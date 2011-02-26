#ifndef COPTIONS_H_
#define COPTIONS_H_

#include <PA9.h>
#include "define.h"

// Displays the options and handle the user interaction with the menu.
// It allows to:
//    - modify the music volume
//    - modify the card speed
//    - exit the game
//    - resume the game
class COptions {
 public:
  // Constructor
  COptions(void);
  // Destructor
  virtual ~COptions(void);
  // Display the options menu on the bottom screen
  bool display(int *p_musicVolume, int *p_cardSpeed);
 private:
  // Return the index of the item touched by the stylus and perform the corresponding action
  u16 itemTouched();
  u16 m_itemTouched;
  int m_musicVolume;
  int m_cardSpeed;
  // Copy constructor and operator '=' forbidden
  COptions(const COptions &p_source);
  const COptions &operator=(const COptions &p_right);
};

#endif  // COPTIONS_H_
