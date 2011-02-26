#ifndef CGAME_H_
#define CGAME_H_

#include <PA9.h>
#include "define.h"
#include "CPlayer.h"
#include "CPlayer1.h"
#include "CPlayer2.h"
#include "CDeck.h"
#include "COptions.h"
#include "CCard.h"

class CGame {
 public:
  // Constructor
  CGame(void);
  // Destructor
  virtual ~CGame(void);
  // Initialise the game
  void initGame(int p_musicVolume, int p_cardSpeed, int p_gameMode,
                u8 p_playerOrder);
  // Play the game
  bool play(int *p_musicVolume, int *p_cardSpeed);
  
 private:
  // The two players
  CPlayer1 m_player1;
  CPlayer2 m_player2;
  // Current active and inactive player
  CPlayer * m_playerActive;
  CPlayer * m_playerInactive;
  // Deck object that contains the cards
  CDeck m_deck;
  // Options menu
  COptions m_options;
  // Timer used to make the player statistics blink
  u8 m_count;
  int m_musicVolume;
  int m_cardSpeed;
  // Defines the type of game to be played (MODE_ONEPLAYER, MODE_TWOPLAYERS,
  // MODE_TWOCOMPS, MODE_HOTSEAT, MODE_WIFI)
  int m_gameMode;
  // Defines the players type (HUMAN, COMPUTER, HUMAN_SEND, HUMAN_GET)
  int m_player1ID;
  int m_player2ID;
  // Copy constructor and operator '=' forbidden
  CGame(const CGame &p_source);
  const CGame &operator=(const CGame &p_right);
};

#endif
