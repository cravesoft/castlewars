#include "CPlayer.h"

// sounds
#include "sound1.h"
#include "sound2.h"
#include "sound3.h"
#include "sound4.h"
#include "sound5.h"
#include "sound6.h"
#include "sound7.h"
#include "sound8.h"

CPlayer::CPlayer(void)
    : m_attackv(2),
      m_attack(5),
      m_defensev(2),
      m_defense(5),
      m_magicv(2),
      m_magic(5),
      m_castle(30),
      m_wall(10),
      m_init(false),
      m_state(PLAYER_STATE_PLAYING) {}

CPlayer::~CPlayer(void) {}

void CPlayer::reset(void) {
  m_state = PLAYER_STATE_PLAYING;
  m_attackv = 2;
  m_attack = 5;
  m_defensev = 2;
  m_defense = 5;
  m_magicv = 2;
  m_magic = 5;
  m_castle = 30;
  m_wall = 10;
}

void CPlayer::displayStats(void) {
  m_attackv = (m_attackv < 1) ? 1 : m_attackv;
  m_attackv = (m_attackv >= 999) ? 999 : m_attackv;
  m_attack = (m_attack < 0) ? 0 : m_attack;
  m_attack = (m_attack >= 999) ? 999 : m_attack;
  m_defensev = (m_defensev < 1) ? 1 : m_defensev;
  m_defensev = (m_defensev >= 999) ? 999 : m_defensev;
  m_defense = (m_defense < 0) ? 0 : m_defense;
  m_defense = (m_defense >= 999) ? 999 : m_defense;
  m_magicv = (m_magicv < 1) ? 1 : m_magicv;
  m_magicv = (m_magicv >= 999) ? 999 : m_magicv;
  m_magic = (m_magic < 0) ? 0 : m_magic;
  m_magic = (m_magic >= 999) ? 999 : m_magic;
  m_wall = (m_wall < 0) ? 0 : m_wall;
  m_wall = (m_wall >= 100) ? 100 : m_wall;
  if (m_castle < 0)  // lose
    m_castle = 0;
  if (m_castle >= 100)  // win
    m_castle = 100;
}

void CPlayer::newTurn(void) {
  m_attack += m_attackv;
  m_defense += m_defensev;
  m_magic += m_magicv;
}

bool CPlayer::displayHand(void) {
  typecard card;
  bool visible;
  
  if ((m_playerID == HUMAN) || (m_playerID == HUMAN_SEND))
    visible = true;
  else
    visible = false;
    
  if (m_init) {
    for (int i=0; i<8; i++) {
      card = m_hand[i]->getCard();
      m_hand[i]->setPlayable(this->isPlayable(card));
      m_hand[i]->display(visible);
    }
    return true;
  }
  else
    return false;
}

bool CPlayer::isPlayable(typecard card) {
  switch (card.first) {
    case 0:
      switch (card.second) {
        case 0:
          return (m_attack >= 1);
          break;
        case 1:
          return (m_attack >= 2);
          break;
        case 2:
          return (m_attack >= 2);
          break;
        case 3:
          return (m_attack >= 4);
          break;
        case 4:
          return (m_attack >= 8);
          break;
        case 5:
          return (m_attack >= 10);
          break;
        case 6:
          return (m_attack >= 12);
          break;
        case 7:
          return (m_attack >= 15);
          break;
        case 8:
          return (m_attack >= 18);
          break;
        case 9:
          return (m_attack >= 28);
          break;
        default:
          PA_OutputText(1,0,0,"This card number does not exist.");
          break;
      }
      break;
    case 1:
      switch (card.second) {
        case 0:
          return (m_defense >= 1);
          break;
        case 1:
          return (m_defense >= 1);
          break;
        case 2:
          return (m_defense >= 3);
          break;
        case 3:
          return ((m_defense >= 3) && (m_wall >= 4));
          break;
        case 4:
          return (m_defense >= 5);
          break;
        case 5:
          return (m_defense >= 8);
          break;
        case 6:
          return (m_defense >= 10);
          break;
        case 7:
          return (m_defense >= 12);
          break;
        case 8:
          return (m_defense >= 18);
          break;
        case 9:
          return (m_defense >= 39);
          break;
        default:
          PA_OutputText(1,0,0,"This card number does not exist.");
          break;
      }
      break;
    case 2:
      switch (card.second) {
        case 0:
          return (m_magic >= 4);
          break;
        case 1:
          return (m_magic >= 4);
          break;
        case 2:
          return (m_magic >= 4);
          break;
        case 3:
          return (m_magic >= 4);
          break;
        case 4:
          return (m_magic >= 4);
          break;
        case 5:
          return (m_magic >= 4);
          break;
        case 6:
          return (m_magic >= 8);
          break;
        case 7:
          return (m_magic >= 21);
          break;
        case 8:
          return (m_magic >= 22);
          break;
        case 9:
          return (m_magic >= 45);
          break;
        default:
          PA_OutputText(1,0,0,"This card number does not exist.");
          break;
      }
      break;
    default:
      PA_OutputText(1,0,0,"This card type does not exist.");
      break; 
  }
  return false;
}

void CPlayer::hideHand(void) const {
  for (int i=7; i>=0; i--) {
    if (m_hand[i] != NULL)
      m_hand[i]->hide();
  }
}

void CPlayer::initHand(CDeck &p_deck, const bool display, const int p_cardSpeed) {
  typecard card;
  bool visible;
  
  if ((m_playerID == HUMAN) || (m_playerID == HUMAN_SEND))
    visible = true;
  else
    visible = false;
  
  for (int i=0; i<8; i++) {
    p_deck.pickCard(&card, m_playerID);
    m_hand[i] = new CCard(i, card.first, card.second);
    m_hand[i]->setPlayable(this->isPlayable(card));
    if (display) {
#ifndef DEBUG
      AS_SoundQuickPlay(sound1);
#endif
      m_hand[i]->moveCardFromDeck(p_cardSpeed, visible);
    }
  }
  m_init = true;
}

void CPlayer::pickCard(CDeck &p_deck, const int p_cardSpeed) {
  typecard card;
  bool visible;
  
  if ((m_playerID == HUMAN) || (m_playerID == HUMAN_SEND))
    visible = true;
  else
    visible = false;
    
  for (int i=0; i<8; i++) {
    if (m_hand[i] == NULL) {
      p_deck.pickCard(&card, m_playerID);
      m_hand[i] = new CCard(i, card.first, card.second);
      m_hand[i]->moveCardFromDeck(p_cardSpeed, visible);
      break;
    }
  }
}

void CPlayer::useCard(typecard card) {
  switch (card.first) {
    case 0:
      switch (card.second) {
        case 0:
          m_attack--;
          break;
        case 1:
          m_attack-=2;
          break;
        case 2:
          m_attack-=2;
          break;
        case 3:
          m_attack-=4;
          break;
        case 4:
          m_attack-=8;
          break;
        case 5:
          m_attack-=10;
          break;
        case 6:
          m_attack-=12;
          break;
        case 7:
          m_attack-=15;
          break;
        case 8:
          m_attack-=18;
          break;
        case 9:
          m_attack-=28;
          break;
        default:
          PA_OutputText(1,0,0,"This card number does not exist.");
          break;
      }
      break;
    case 1:
      switch (card.second) {
        case 0:
          m_defense--;
          break;
        case 1:
          m_defense--;
          break;
        case 2:
          m_defense-=3;
          break;
        case 3:
          m_defense-=3;
          break;
        case 4:
          m_defense-=5;
          break;
        case 5:
          m_defense-=8;
          break;
        case 6:
          m_defense-=10;
          break;
        case 7:
          m_defense-=12;
          break;
        case 8:
          m_defense-=18;
          break;
        case 9:
          m_defense-=39;
          break;
        default:
          PA_OutputText(1,0,0,"This card number does not exist.");
          break;
      }
      break;
    case 2:
      switch (card.second) {
        case 0:
          m_magic-=4;
          break;
        case 1:
          m_magic-=4;
          break;
        case 2:
          m_magic-=4;
          break;
        case 3:
          m_magic-=4;
          break;
        case 4:
          m_magic-=4;
          break;
        case 5:
          m_magic-=4;
          break;
        case 6:
          m_magic-=8;
          break;
        case 7:
          m_magic-=21;
          break;
        case 8:
          m_magic-=22;
          break;
        case 9:
          m_magic-=45;
          break;
        default:
          PA_OutputText(1,0,0,"This card number does not exist.");
          break;
      }
      break;
    default:
      PA_OutputText(1,0,0,"This card type does not exist.");
      break; 
  }
}

void CPlayer::heal(const typecard card, const int exchangestats[3]) {
  m_attackvc = 0;
  m_attackc = 0;
  m_defensevc = 0;
  m_defensec = 0;
  m_magicvc = 0;
  m_magicc = 0;
  m_castlec = 0;
  m_wallc = 0;
  
  switch (card.first) {
    case 0:
      switch (card.second) {
        case 0:
          break;
        case 1:
          break;
        case 2:
          break;
        case 3:
          break;
        case 4:
          m_attackvc++;
          m_attackv++;
#ifndef DEBUG
          AS_SoundQuickPlay(sound2);
#endif
          break;
        case 5:
          break;
        case 6:
          break;
        case 7:
          m_attackc = (exchangestats[0] < 0) ? 5-ABS(exchangestats[0]) : 5;
          m_defensec = (exchangestats[1] < 0) ? 5-ABS(exchangestats[1]) : 5;
          m_magicc = (exchangestats[2] < 0) ? 5-ABS(exchangestats[2]) : 5;
          m_attack += (exchangestats[0] < 0) ? 5-ABS(exchangestats[0]) : 5;
          m_defense += (exchangestats[1] < 0) ? 5-ABS(exchangestats[1]) : 5;
          m_magic += (exchangestats[2] < 0) ? 5-ABS(exchangestats[2]) : 5;
#ifndef DEBUG
          AS_SoundQuickPlay(sound4);
#endif
          break;
        case 8:
          break;
        case 9:
          break;
        default:
          PA_OutputText(1,0,0,"This card number does not exist.");
          break;
      }
      break;
    case 1:
      switch (card.second)
      {
        case 0:
          m_wallc = (m_wall < 100-3) ? 3 : 100-m_wall;
          m_wall+=3;
#ifndef DEBUG
          AS_SoundQuickPlay(sound8);
#endif
          break;
        case 1:
          m_castlec = (m_castle < 100-2) ? 2 : 100-m_castle;
          m_castle+=2;
#ifndef DEBUG
          AS_SoundQuickPlay(sound7);
#endif
          break;
        case 2:
          m_wallc = (m_wall < 100-6) ? 6 : 100-m_wall;
          m_wall+=6;
#ifndef DEBUG
          AS_SoundQuickPlay(sound8);
#endif
          break;
        case 3:
          m_wallc = -4;
          m_castlec = (m_castle < 100-8) ? 8 : 100-m_castle;
          m_wall-=4;
          m_castle+=8;
#ifndef DEBUG
          AS_SoundQuickPlay(sound5);
          AS_SoundQuickPlay(sound7);
#endif
          break;
        case 4:
          m_castlec = (m_castle < 100-5) ? 5 : 100-m_castle;
          m_castle+=5;
#ifndef DEBUG
          AS_SoundQuickPlay(sound7);
#endif
          break;
        case 5:
          m_defensevc++;
          m_defensev++;
#ifndef DEBUG
          AS_SoundQuickPlay(sound2);
#endif
          break;
        case 6:
          m_castlec = (m_castle < 100-8) ? 8 : 100-m_castle;
          m_castle+=8;
#ifndef DEBUG
          AS_SoundQuickPlay(sound7);
#endif
          break;
        case 7:
          m_wallc = (m_wall < 100-22) ? 22 : 100-m_wall;
          m_wall+=22;
#ifndef DEBUG
          AS_SoundQuickPlay(sound8);
#endif
          break;
        case 8:
          m_castlec = (m_castle < 100-20) ? 20 : 100-m_castle;
          m_castle+=20;
#ifndef DEBUG
          AS_SoundQuickPlay(sound7);
#endif
          break;
        case 9:
          m_castlec = (m_castle < 100-32) ? 32 : 100-m_castle;
          m_castle+=32;
#ifndef DEBUG
          AS_SoundQuickPlay(sound7);
#endif
          break;
        default:
          PA_OutputText(1,0,0,"This card number does not exist.");
          break;
      }
      break;
    case 2:
      switch (card.second)
      {
        case 0:
          m_defensec = 8;
          m_defense+=8;
#ifndef DEBUG
          AS_SoundQuickPlay(sound4);
#endif
          break;
        case 1:
          m_magicc = 8;
          m_magic+=8;
#ifndef DEBUG
          AS_SoundQuickPlay(sound4);
#endif
          break;
        case 2:
          m_attackc = 8;
          m_attack+=8;
#ifndef DEBUG
          AS_SoundQuickPlay(sound4);
#endif
          break;
        case 3:
          break;
        case 4:
          break;
        case 5:
          break;
        case 6:
          m_magicvc++;
          m_magicv++;
#ifndef DEBUG
          AS_SoundQuickPlay(sound2);
#endif
          break;
        case 7:
          break;
        case 8:
          m_castlec = (m_castle < 100-22) ? 22 : 100-m_castle;
          m_castle+=22;
#ifndef DEBUG
          AS_SoundQuickPlay(sound7);
#endif
          break;
        case 9:
          m_attackvc++;
          m_attackc++;
          m_defensevc++;
          m_defensec++;
          m_magicvc++;
          m_magicc++;
          m_castlec++;
          m_wallc = (m_wall < 100-1) ? 1 : 0;
          m_attackv++;
          m_attack++;
          m_defensev++;
          m_defense++;
          m_magicv++;
          m_magic++;
          m_castle++;
          m_wall++;
#ifndef DEBUG
          AS_SoundQuickPlay(sound2);
          AS_SoundQuickPlay(sound4);
          AS_SoundQuickPlay(sound7);
          AS_SoundQuickPlay(sound8);
#endif
          break;
        default:
          PA_OutputText(1,0,0,"This card number does not exist.");
          break;
      }
      break;
    default:
      PA_OutputText(1,0,0,"This card type does not exist.");
      break; 
  }
  if (m_castle >= 100)
    goToState(PLAYER_STATE_WIN);
}

void CPlayer::damage(const typecard card, int exchangestats[3]) {
  m_attackvc = 0;
  m_attackc = 0;
  m_defensevc = 0;
  m_defensec = 0;
  m_magicvc = 0;
  m_magicc = 0;
  m_castlec = 0;
  m_wallc = 0;
  
  switch (card.first) {
    case 0:
      switch (card.second) {
        case 0:
#ifndef DEBUG
          if (m_wall > 0)
            AS_SoundQuickPlay(sound5);
#endif
          m_wallc = (m_wall > 2) ? -2 : -m_wall;
          if ((m_wall -= 2) < 0) {
            m_castlec = (m_castle > ABS(m_wall)) ? m_wall : -m_castle;
            m_castle += m_wall;
#ifndef DEBUG
            AS_SoundQuickPlay(sound6);
#endif
          }
          break;
        case 1:
#ifndef DEBUG
          if (m_wall > 0)
            AS_SoundQuickPlay(sound5);
#endif
          m_wallc = (m_wall > 3) ? -3 : -m_wall;
          if ((m_wall -= 3) < 0) {
            m_castlec = (m_castle > ABS(m_wall)) ? m_wall : -m_castle;
            m_castle += m_wall;
#ifndef DEBUG
            AS_SoundQuickPlay(sound6);
#endif
          }
          break;
        case 2:
#ifndef DEBUG
          if (m_wall > 0)
            AS_SoundQuickPlay(sound5);
#endif
          m_wallc = (m_wall > 4) ? -4 : -m_wall;
          if ((m_wall -= 4) < 0) {
            m_castlec = (m_castle > ABS(m_wall)) ? m_wall : -m_castle;
            m_castle += m_wall;
#ifndef DEBUG
            AS_SoundQuickPlay(sound6);
#endif
          }
          break;
        case 3:
#ifndef DEBUG
          if (m_wall > 0)
            AS_SoundQuickPlay(sound5);
#endif
          m_wallc = (m_wall > 6) ? -6 : -m_wall;
          if ((m_wall -= 6) < 0) {
            m_castlec = (m_castle > ABS(m_wall)) ? m_wall : -m_castle;
            m_castle += m_wall;
#ifndef DEBUG
            AS_SoundQuickPlay(sound6);
#endif
          }
          break;
        case 4:
          break;
        case 5:
#ifndef DEBUG
          if (m_wall > 0)
            AS_SoundQuickPlay(sound5);
#endif
          m_wallc = (m_wall > 12) ? -12 : -m_wall;
          if ((m_wall -= 12) < 0) {
            m_castlec = (m_castle > ABS(m_wall)) ? m_wall : -m_castle;
            m_castle += m_wall;
#ifndef DEBUG
            AS_SoundQuickPlay(sound6);
#endif
          }
          break;
        case 6:
#ifndef DEBUG
          AS_SoundQuickPlay(sound3);
#endif
          m_attackc = (m_attack > 4) ? -4 : -m_attack;
          m_defensec = (m_defense > 4) ? -4 : -m_defense;
          m_magicc = (m_magic > 4) ? -4 : -m_magic;
          m_attack -= 4;
          m_defense -= 4;
          m_magic -= 4;
          break;
        case 7:
#ifndef DEBUG
          AS_SoundQuickPlay(sound3);
#endif
          m_attackc = (m_attack > 5) ? -5 : -m_attack;
          m_defensec = (m_defense > 5) ? -5 : -m_defense;
          m_magicc = (m_magic > 5) ? -5 : -m_magic;
          m_attack -= 5;
          m_defense -= 5;
          m_magic -= 5;
          exchangestats[0] = m_attack;
          exchangestats[1] = m_defense;
          exchangestats[2] = m_magic;
          break;
        case 8:
#ifndef DEBUG
          AS_SoundQuickPlay(sound6);
#endif
          m_castlec = (m_castle > 10) ? -10 : -m_castle;
          m_castle -= 10;
          break;
        case 9:
#ifndef DEBUG
          if (m_wall > 0)
            AS_SoundQuickPlay(sound5);
#endif
          m_wallc = (m_wall > 32) ? -32 : -m_wall;
          if ((m_wall -= 32) < 0) {
            m_castlec = (m_castle > ABS(m_wall)) ? m_wall : -m_castle;
            m_castle += m_wall;
#ifndef DEBUG
            AS_SoundQuickPlay(sound6);
#endif
          }
          break;
        default:
          PA_OutputText(1,0,0,"This card number does not exist.");
          break;
      }
      break;
    case 1:
      switch (card.second) {
        case 0:
          break;
        case 1:
          break;
        case 2:
          break;
        case 3:
          break;
        case 4:
          break;
        case 5:
          break;
        case 6:
          m_castlec = (m_castle > 4) ? -4 : -m_castle;
          m_castle-=4;
#ifndef DEBUG
          AS_SoundQuickPlay(sound6);
#endif
          break;
        case 7:
          break;
        case 8:
          break;
        case 9:
          break;
        default:
          PA_OutputText(1,0,0,"This card number does not exist.");
          break;
      }
      break;
    case 2:
      switch (card.second) {
        case 0:
          break;
        case 1:
          break;
        case 2:
          break;
        case 3:
          m_defensec = (m_defense > 8) ? -8 : -m_defense;
          m_defense -= 8;
#ifndef DEBUG
          AS_SoundQuickPlay(sound3);
#endif
          break;
        case 4:
          m_magicc = (m_magic > 8) ? -8 : -m_magic;
          m_magic -= 8;
#ifndef DEBUG
          AS_SoundQuickPlay(sound3);
#endif
          break;
        case 5:
          m_attackc = (m_attack > 8) ? -8 : -m_attack;
          m_attack -= 8;
#ifndef DEBUG
          AS_SoundQuickPlay(sound3);
#endif
          break;
        case 6:
          break;
        case 7:
#ifndef DEBUG
          if (m_wall > 0)
            AS_SoundQuickPlay(sound5);
#endif
          m_wallc = (m_wall > 25) ? -25 : -m_wall;
          if ((m_wall -= 25) < 0) {
            m_castlec = (m_castle > ABS(m_wall)) ? m_wall : -m_castle;
            m_castle += m_wall;
#ifndef DEBUG
            AS_SoundQuickPlay(sound6);
#endif
          }
          break;
        case 8:
          break;
        case 9:
#ifndef DEBUG
          AS_SoundQuickPlay(sound3);
          if (m_wall > 0)
            AS_SoundQuickPlay(sound5);
          AS_SoundQuickPlay(sound6);
#endif
          
          m_wallc = (m_wall > 0) ? -1 : 0;
          m_attackvc = (m_attackv > 1) ? -1 : 0;
          m_attackc = (m_attack > 0) ? -1 : 0;
          m_defensevc = (m_defensev > 1) ? -1 : 0;
          m_defensec = (m_defense > 0) ? -1 : 0;
          m_magicvc = (m_magicv > 1) ? -1 : 0;
          m_magicc = (m_magic > 0) ? -1 : 0;          
          m_castlec--;
          
          m_attackv--;
          m_attack--;
          m_defensev--;
          m_defense--;
          m_magicv--;
          m_magic--;
          m_castle--;
          m_wall--;
          break;
        default:
          PA_OutputText(1,0,0,"This card number does not exist.");
          break;
      }
      break;
    default:
      PA_OutputText(1,0,0,"This card type does not exist.");
      break; 
  }
  if (m_castle <= 0)
    goToState(PLAYER_STATE_LOSE);
}

bool CPlayer::playCard(typecard* card, bool* pdiscard, const int p_cardSpeed) {
  u8 cardnumber;
  bool visible;
  if ((m_playerID == HUMAN) || (m_playerID == HUMAN_SEND))
    visible = true;
  else
    visible = false;
  if ((m_playerID == HUMAN) || (m_playerID == HUMAN_SEND)) {
    for (cardnumber=0; cardnumber<8; cardnumber++) {
      if ((Pad.Held.R) || (Pad.Held.L)) {
        m_hand[cardnumber]->setDiscard(true);
        *pdiscard = true;
        if (m_hand[cardnumber]->isTouched()) {
#ifndef DEBUG
          AS_SoundQuickPlay(sound1);
#endif
          m_hand[cardnumber]->moveCardOnDeck(p_cardSpeed, visible);
          *card = m_hand[cardnumber]->getCard();
          delete m_hand[cardnumber];
          m_hand[cardnumber] = NULL;
          if (m_playerID == HUMAN_SEND) {
            l_wifi.sendIntInfo(cardnumber);
            l_wifi.sendBoolInfo(*pdiscard);      
          }
          return true;
        }     
      } else {
        m_hand[cardnumber]->setDiscard(false);
        *pdiscard = false;
        if (m_hand[cardnumber]->isTouched() && m_hand[cardnumber]->isPlayable()) {
#ifndef DEBUG
          AS_SoundQuickPlay(sound1);
#endif
          m_hand[cardnumber]->moveCardOnDeck(p_cardSpeed, visible);
          *card = m_hand[cardnumber]->getCard();
          this->useCard(*card);
          delete m_hand[cardnumber];
          m_hand[cardnumber] = NULL;
          if (m_playerID == HUMAN_SEND) {
            l_wifi.sendIntInfo(cardnumber);
            l_wifi.sendBoolInfo(*pdiscard);      
          }
          return true;
        }
      }
    }
  } else {
    if (m_playerID == HUMAN_GET) {
      cardnumber  = l_wifi.getIntInfo();
      *pdiscard = l_wifi.getBoolInfo();      
    } else {
      if (m_playerID == COMPUTER)
        chooseCard(&cardnumber, pdiscard);
    }
#ifndef DEBUG
    AS_SoundQuickPlay(sound1);
#endif
    m_hand[cardnumber]->moveCardOnDeck(p_cardSpeed, visible);
    *card = m_hand[cardnumber]->getCard();
    if (*pdiscard == false)
      this->useCard(*card);
    delete m_hand[cardnumber];
    m_hand[cardnumber] = NULL;
    return true;
  }  
  return false;
}

// Return a random card
// If none are playable, discard a random card
// TODO: A true IA
void CPlayer::chooseCard(u8 *cardnumber, bool* pdiscard) {
  bool isplayable = false;
  for (*cardnumber=0; *cardnumber<8; (*cardnumber)++)
    if (m_hand[*cardnumber]->isPlayable()) {
      isplayable = true;
      break;
    }
  if (isplayable) {
    *pdiscard = false;
    *cardnumber = PA_RandMax(7);
    while (!m_hand[*cardnumber]->isPlayable())
      *cardnumber = PA_RandMax(7);
  } else {
    *pdiscard = true;
    *cardnumber = PA_RandMax(7);
  }
}
