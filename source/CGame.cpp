#include "CGame.h"

// Gfx
#include "gfx/upscreen.pal.c"
#include "gfx/upscreen.c"
#include "gfx/bottomscreen.pal.c"
#include "gfx/bottomscreen.c"
#include "gfx/win.pal.c"
#include "gfx/win.c"
#include "gfx/lose.pal.c"
#include "gfx/lose.c"

CGame::CGame(void)
    : m_playerActive(NULL),
      m_playerInactive(NULL),
      m_count(0),
      m_gameMode(1) {
  m_musicVolume = MUSIC_VOLUME;
  m_cardSpeed = CARD_SPEED;
}

CGame::~CGame(void) {}

void CGame::initGame(int p_musicVolume, int p_cardSpeed, int p_gameMode,
                     u8 p_playerOrder) {
  m_musicVolume = p_musicVolume;
  m_cardSpeed = p_cardSpeed;
  m_gameMode = p_gameMode;
  // Display the background for the top screen
  PA_EasyBgLoad(1, 2, upscreen);
  // Define the players' type
  switch(m_gameMode) {
    case MODE_ONEPLAYER:
      m_player1ID = HUMAN;
      m_player2ID = COMPUTER;
      break;
    case MODE_TWOCOMPS:
      m_player1ID = COMPUTER;
      m_player2ID = COMPUTER;
      break;
    case MODE_HOTSEAT:
      m_player1ID = HUMAN;
      m_player2ID = HUMAN;
      break;
    case MODE_WIFI:
      if (p_playerOrder == 0) {
        m_player1ID = HUMAN_SEND;
        m_player2ID = HUMAN_GET;
      }
      else {
        m_player1ID = HUMAN_GET;
        m_player2ID = HUMAN_SEND;
      }
      break;
    default:
      PA_OutputText(1,0,0,"This game mode does not exist.");
  }
  // Delete the background at the bottom screen if the game mode is MODE_WIFI
  if (m_gameMode != MODE_WIFI)
    PA_DeleteBg(0, 0);
  // Initialize the players
  m_player1.reset();
  m_player2.reset();
  m_player1.setIdentity(m_player1ID);
  m_player2.setIdentity(m_player2ID);
  m_player1.displayStats();
  m_player2.displayStats();
  m_player1.displayCastle();
  m_player2.displayCastle();
  // By default, the player 1 starts
  m_playerActive = &m_player1;
  m_playerInactive = &m_player2;
  // Initialize and display the deck of cards
  m_deck.reset();
  m_deck.display();
  // Fade from white
  for (s8 l_i = 31; l_i > 0; l_i--) {
  	PA_SetBrightness(1, l_i);
  	PA_WaitForVBL();
  	PA_WaitForVBL();
  }
  // Wait for the fist player to start the game (hotseat mode only)
  if (m_gameMode == MODE_HOTSEAT) {
    m_playerActive->displayMessage();
    PA_WaitForVBL();
    while(!Stylus.Newpress)
      PA_WaitForVBL();
    m_playerActive->hideMessage();
  }
  PA_WaitForVBL();
  // Initialise and display the first player's hand
  m_playerActive->initHand(m_deck, true, m_cardSpeed);
}

bool CGame::play(int *p_musicVolume, int *p_cardSpeed) {
  int exchangestats[3];
  bool discard;
  int blink;
  typecard playedCard;
  // end game?
  if ((m_playerActive->getState() == PLAYER_STATE_WIN) ||
      (m_playerInactive->getState() == PLAYER_STATE_LOSE) ||
      (m_playerInactive->getState() == PLAYER_STATE_WIN) ||
      (m_playerActive->getState() == PLAYER_STATE_LOSE)) {
    if (Stylus.Newpress) {
      m_deck.hideDeck();
      m_player1.hideStats();
      m_player2.hideStats();
      m_player2.hideCastle();
      m_player1.hideCastle();
      return true;
    }
  } else {
    if (Pad.Held.Start) {  // display options if start is pressed
      m_playerActive->displayStats();
      m_playerActive->hideHand();
      if (m_options.display(&m_musicVolume, &m_cardSpeed)) {
        *p_musicVolume = m_musicVolume;
        *p_cardSpeed = m_cardSpeed;
        m_deck.hideDeck();
        m_player1.hideStats();
        m_player2.hideStats();
        m_player2.hideCastle();
        m_player1.hideCastle();
        return true;
      }
      PA_ResetBgSysScreen(0);
      PA_Init16cBg(0, 1);
      PA_EasyBgLoad(0, 2, bottomscreen);
      m_playerActive->displayHand();
    }
    // make the active player statistics blink
    if (m_count > 20) {
      m_playerActive->hideStats();
      if (m_count > 25) {
        m_playerActive->displayStats();
        m_count = 0;
      }
    }
    m_count++;
    // Play or discard a card
    if (m_playerActive->playCard(&playedCard, &discard, m_cardSpeed)) {
      m_playerActive->displayStats();
      PA_WaitForVBL();
      m_deck.discardCard(playedCard, discard); // Put playedCard into the stack
      if (!discard) {  // Play playedCard
        m_playerInactive->damage(playedCard, exchangestats);
        m_playerActive->heal(playedCard, exchangestats);
        m_playerActive->displayStats();
        m_playerInactive->displayStats(); 
        m_playerActive->displayCastle();
        m_playerInactive->displayCastle();
        // Display the gains and losses
        blink = 0;
        while (blink < 4) {
          m_playerActive->displayChanges();
          m_playerInactive->displayChanges();
          if (m_count > 20) {
            PA_16cErase (1);
            if (m_count > 25) {
              blink ++;
              m_count = 0;
            }
          }
          m_count++;
          PA_WaitForVBL();
        }
      }
      // end game?
      if ((m_playerActive->getState() == PLAYER_STATE_WIN) ||
          (m_playerInactive->getState() == PLAYER_STATE_LOSE)) {
        if ((m_gameMode == MODE_ONEPLAYER) || (m_gameMode == MODE_WIFI)) {
          if ((m_playerActive->getIdentity() == HUMAN) ||
              (m_playerActive->getIdentity() == HUMAN_SEND))
          {
            PA_EasyBgLoad(0, 0, win);
          } else {
            PA_EasyBgLoad(0, 0, lose);
          }
        } else {
          m_playerActive->displayWin();
        }
        m_playerActive->hideHand();
      } else {
        // Pick a new card and hide the player's hand
        m_playerActive->pickCard(m_deck, m_cardSpeed);
        m_playerActive->hideHand();
        // Change the actve player
        if (m_playerActive == &m_player1) {
          m_playerActive = &m_player2;
          m_playerInactive = &m_player1;
        } else {
          m_playerActive = &m_player1;
          m_playerInactive = &m_player2;
        }
        // Wait for the current player to take his turn (hotseat mode only)
        if (m_gameMode == MODE_HOTSEAT) {
          m_playerActive->displayMessage();
          PA_WaitForVBL();
          while(!Stylus.Newpress)
            PA_WaitForVBL();
          m_playerActive->hideMessage();
        }
        PA_WaitForVBL();
        // Update materials of active player before displaying his statistics
        m_playerActive->newTurn();
        m_playerActive->displayStats();
        // If the player does not have a hand yet (first turn),
        // initialize his hand
        if (!m_playerActive->displayHand())  
          m_playerActive->initHand(m_deck, true, m_cardSpeed);
      }
    }
  }
  *p_musicVolume = m_musicVolume;
  *p_cardSpeed = m_cardSpeed;
  return false;
}
