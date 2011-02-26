#ifndef CPlayer1_H_
#define CPlayer1_H_

#include <PA9.h>
#include <sstream>
#include "define.h"
#include "CPlayer.h"

// Gfx
#include "gfx/player1turn.c"
#include "gfx/player1turn.pal.c"
#include "gfx/player1win.c"
#include "gfx/player1win.pal.c"

class CPlayer1 : public CPlayer {
 public:
  // Constructor
  CPlayer1(void);
  // Destructor
  virtual ~CPlayer1(void);
  // Set to the initial position
  virtual void reset(void);
  // Display the statistics of the player at the top screen
  void displayStats();
  // Hide the statistics of the player at the top screen
  void hideStats();  
  // Display the castle and player's wall at the top screen
  void displayCastle(void);
  // Hide the castle and player's wall
  void hideCastle(void);
  // Display the variation of the statistics
  void displayChanges();
  // Display the player's turn
  inline void displayMessage() { PA_EasyBgLoad(0, 0, player1turn); }
  //Display the win message
  inline void displayWin() { PA_EasyBgLoad(0, 0, player1win); }

 private:
  // Forbidden
  CPlayer1(const CPlayer1 &p_source);
  const CPlayer1 &operator=(const CPlayer1 &p_right);
};

#endif  // CPlayer1_H_
