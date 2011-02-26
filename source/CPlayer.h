#ifndef CPLAYER_H_
#define CPLAYER_H_

#include <PA9.h>
#include "define.h"
#include "CDeck.h"
#include "CCard.h"
#include "CWifiHandler.h"

class CPlayer {
 public:
  // Constructor
  CPlayer(void);
  // Destructor
  virtual ~CPlayer(void);
  // Reset player
  void reset(void);
  // Go to another state
  inline void goToState(const T_PLAYER_STATE p_newState) { m_state = p_newState; }
  // Display the statistics of the player at the top screen
  virtual void displayStats(void);
  // Hide the statistics of the player at the top screen
  virtual void hideStats(void) = 0;
  virtual void hideCastle(void) = 0;
  // Display the castle and the wall of the player at the top screen
  virtual void displayCastle(void) = 0;
  // Display the hand of cards of the player at the bottom screen
  bool displayHand(void);
  // Display the hand of cards of the player at the bottom screen
  void hideHand(void) const;
  // Initialize the hand of cards of the player
  void initHand(CDeck &p_deck, const bool display, const int p_cardSpeed);
  // Pick a card in the deck
  void pickCard(CDeck &p_deck, const int p_cardSpeed);
  // Play (or discard) a card
  bool playCard(typecard* card, bool* pdiscard, const int p_cardSpeed);
  // Return true if card is playable
  bool isPlayable(typecard card);
  // Remove the materials needed to use card
  void useCard(typecard card);
  // Use a card to heal the player
  void heal(const typecard card, const int exchangestats[3]);
  // Use a card to damage the player
  void damage(const typecard card, int exchangestats[3]);
  // Return the current player state
  inline const T_PLAYER_STATE getState(void) const { return m_state; }
  // Add the velocity to the player stats
  void newTurn(void);
  // Display the player's "new turn" message
  virtual void displayMessage() = 0;
  // Display the win message
  virtual void displayWin() = 0;
  // Hide the player's message
  inline void hideMessage() { PA_DeleteBg (0, 0); }
  // Display the card effect
  virtual void displayChanges() = 0;
  // Set the player's identity
  inline void setIdentity(int playerID) { m_playerID = playerID; }
  // Get the player's identity
  inline int getIdentity(void) { return m_playerID; }
  // Choose a new card to be played by the IA
  void chooseCard(u8 *cardnumber, bool* pdiscard);

 protected:
  // Player stats
  int m_attackv;
  int m_attack;
  int m_defensev;
  int m_defense;
  int m_magicv;
  int m_magic;
  int m_castle;
  int m_wall;
  // Stats velocity
  int m_attackvc;
  int m_attackc;
  int m_defensevc;
  int m_defensec;
  int m_magicvc;
  int m_magicc;
  int m_castlec;
  int m_wallc;
  // true if hand has been initialized
  bool m_init;
  // Player type (HUMAN, COMPUTER, HUMAN_GET or HUMAN_SEND)
  int m_playerID;
  // Player cards
  CCard* m_hand[8];

 private:
  // Player state
  T_PLAYER_STATE m_state;
  // Forbidden
  CPlayer(const CPlayer &p_source);
  const CPlayer &operator=(const CPlayer &p_right);
};

#endif  // CPLAYER_H_
