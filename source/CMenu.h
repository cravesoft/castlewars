#ifndef CMENU_H_
#define CMENU_H_

#include <PA9.h>
#include "define.h"
#include "CGame.h"
#include "CWifiHandler.h"

// Displays the main menu and handle the user interaction with it.
// It allows to:
//    - select a game mode and start a game
//    - see the instructions
class CMenu {
 public:
  // Constructor
  CMenu(void);
  // Destructor
  virtual ~CMenu(void);
  // Display the menu
  void displayMenu(void);

 private:
  // Display the instructions to play the game
  void displayInstructions();
  // Return the index of the item touched by the stylus
  u16 itemTouched();
  u16 m_itemTouched;
  int m_musicVolume;
  int m_cardSpeed;
  u8 m_playerOrder;  // Player order when using a Wifi connection
                     // 0 means this player starts first
  // Copy constructor and operator '=' forbidden
  CMenu(const CMenu &p_source);
  const CMenu &operator=(const CMenu &p_right);
};

#endif  // CMENU_H_
