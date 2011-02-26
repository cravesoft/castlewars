#ifndef CPlayer2_H_
#define CPlayer2_H_

#include <PA9.h>
#include <sstream>
#include "define.h"
#include "CPlayer.h"

// Gfx
#include "gfx/player2turn.c"
#include "gfx/player2turn.pal.c"
#include "gfx/player2win.c"
#include "gfx/player2win.pal.c"

class CPlayer2 : public CPlayer {
 public:
  // Constructor
  CPlayer2(void);
  // Destructor
  virtual ~CPlayer2(void);
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
  // Display the player's turn screen
  inline void displayMessage() { PA_EasyBgLoad(0, 0, player2turn); }
  //Display the win message
  inline void displayWin() { PA_EasyBgLoad(0, 0, player2win); }
  
 private:
  // Forbidden
  CPlayer2(const CPlayer2 &p_source);
  const CPlayer2 &operator=(const CPlayer2 &p_right);
};

#endif  // CPlayer2_H_
