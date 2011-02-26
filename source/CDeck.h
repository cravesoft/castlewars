#ifndef CDECK_H_
#define CDECK_H_

#include <PA9.h>
#include <map>
#include "define.h"
#include "CCard.h"
#include "CWifiHandler.h"

class CDeck {
 public:
  // Constructor
  CDeck(void);
  // Destructor
  virtual ~CDeck(void);
  // Reset the deck
  void reset(void);
  // Display the deck at the top screen
  void display(void);
  // Hide the deck at the top screen
  void hideDeck(void);
  // Pick a card in the deck
  void pickCard(typecard* p_card, int p_playerID);
  // Discard a card in the deck
  void discardCard(const typecard card, const bool discarded);
  
 private:
  // Number of cards of each type in the deck
  map<typecard, u8> m_cardfrequency;
  // Forbidden
  CDeck(const CDeck &p_source);
  const CDeck &operator=(const CDeck &p_right);
};

#endif  // CDECK_H_
