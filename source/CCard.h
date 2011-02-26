#ifndef CCARD_H_
#define CCARD_H_

#include <PA9.h>
#include "define.h"

class CCard {
 public:
  // Constructor
  CCard(void);
  // Constructor
  CCard(const u8 p_number, const u8 p_cardtype, const u8 p_cardnumber);
  // Destructor
  virtual ~CCard(void);
  // Display the card at the bottom screen
  void display(bool visible);
  // Hide the card (delete)
  void hide(void);
  // Return the card identity
  inline typecard getCard() { return typecard(m_cardtype, m_cardnumber); }
  // Return true if the card is playable
  inline bool isPlayable() { return m_isPlayable; }
  // Set the card playability based on the player statistics
  inline void setPlayable(const bool p_isPlayable) {
    m_isPlayable = p_isPlayable;
  }
  // Return true if the card is the stylus touches the card
  bool isTouched();
  // Set the discard mode of the card. If pdiscard is true,
  // the message "Discard" is displayed on top of the card  
  void setDiscard(const bool pdiscard);
  // Put this card in the deck
  void moveCardOnDeck(const int p_cardSpeed, bool visible);
  // Get this card from the deck
  void moveCardFromDeck(const int p_cardSpeed, bool visible);
 private:
  u8 m_number;  // Card number in the player's hand. From 0 to 7
  u8 m_palette_number;
  u8 m_sprite_number[2];  // Two sprites for each card
  u16 m_sprite_posx[2];
  u16 m_sprite_posy[2];
  u8 m_cardtype;  // Card type: 0 (Attack), 1 (Defense), 2 (Magic) 
  u8 m_cardnumber;  // Card number: Frome 0 to 9
  bool m_discard;  // true if the card is in discard mode
  bool m_isPlayable; // true if the card is playable
};

#endif  // CCARD_H_
