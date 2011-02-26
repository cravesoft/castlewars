#include "CCard.h"

// Gfx
#include "gfx/backcard.c"
#include "gfx/card.pal.c"
#include "gfx/attack1_1.c"
#include "gfx/attack2_1.c"
#include "gfx/attack3_1.c"
#include "gfx/attack4_1.c"
#include "gfx/attack5_1.c"
#include "gfx/attack6_1.c"
#include "gfx/attack7_1.c"
#include "gfx/attack8_1.c"
#include "gfx/attack9_1.c"
#include "gfx/attack10_1.c"
#include "gfx/attack1_2.c"
#include "gfx/attack2_2.c"
#include "gfx/attack3_2.c"
#include "gfx/attack4_2.c"
#include "gfx/attack5_2.c"
#include "gfx/attack6_2.c"
#include "gfx/attack7_2.c"
#include "gfx/attack8_2.c"
#include "gfx/attack9_2.c"
#include "gfx/attack10_2.c"
#include "gfx/attack1.pal.c"
#include "gfx/attack2.pal.c"
#include "gfx/attack3.pal.c"
#include "gfx/attack4.pal.c"
#include "gfx/attack5.pal.c"
#include "gfx/attack6.pal.c"
#include "gfx/attack7.pal.c"
#include "gfx/attack8.pal.c"
#include "gfx/attack9.pal.c"
#include "gfx/attack10.pal.c"
#include "gfx/defense1_1.c"
#include "gfx/defense2_1.c"
#include "gfx/defense3_1.c"
#include "gfx/defense4_1.c"
#include "gfx/defense5_1.c"
#include "gfx/defense6_1.c"
#include "gfx/defense7_1.c"
#include "gfx/defense8_1.c"
#include "gfx/defense9_1.c"
#include "gfx/defense10_1.c"
#include "gfx/defense1_2.c"
#include "gfx/defense2_2.c"
#include "gfx/defense3_2.c"
#include "gfx/defense4_2.c"
#include "gfx/defense5_2.c"
#include "gfx/defense6_2.c"
#include "gfx/defense7_2.c"
#include "gfx/defense8_2.c"
#include "gfx/defense9_2.c"
#include "gfx/defense10_2.c"
#include "gfx/defense1.pal.c"
#include "gfx/defense2.pal.c"
#include "gfx/defense3.pal.c"
#include "gfx/defense4.pal.c"
#include "gfx/defense5.pal.c"
#include "gfx/defense6.pal.c"
#include "gfx/defense7.pal.c"
#include "gfx/defense8.pal.c"
#include "gfx/defense9.pal.c"
#include "gfx/defense10.pal.c"
#include "gfx/magic1_1.c"
#include "gfx/magic2_1.c"
#include "gfx/magic3_1.c"
#include "gfx/magic4_1.c"
#include "gfx/magic5_1.c"
#include "gfx/magic6_1.c"
#include "gfx/magic7_1.c"
#include "gfx/magic8_1.c"
#include "gfx/magic9_1.c"
#include "gfx/magic10_1.c"
#include "gfx/magic1_2.c"
#include "gfx/magic2_2.c"
#include "gfx/magic3_2.c"
#include "gfx/magic4_2.c"
#include "gfx/magic5_2.c"
#include "gfx/magic6_2.c"
#include "gfx/magic7_2.c"
#include "gfx/magic8_2.c"
#include "gfx/magic9_2.c"
#include "gfx/magic10_2.c"
#include "gfx/magic1.pal.c"
#include "gfx/magic2.pal.c"
#include "gfx/magic3.pal.c"
#include "gfx/magic4.pal.c"
#include "gfx/magic5.pal.c"
#include "gfx/magic6.pal.c"
#include "gfx/magic7.pal.c"
#include "gfx/magic8.pal.c"
#include "gfx/magic9.pal.c"
#include "gfx/magic10.pal.c"

CCard::CCard(void) {}

CCard::CCard(const u8 p_number, const u8 p_cardtype, const u8 p_cardnumber) {
  m_number = p_number;
  m_palette_number = INDEX_PALETTE_NB_CARD + m_number;
  m_sprite_number[0] = INDEX_SPRITE_NB_CARD + 2*m_number;
  m_sprite_number[1] = m_sprite_number[0] + 1;
  m_cardtype = p_cardtype;
  m_cardnumber = p_cardnumber;
  // Get card position according to the card number in the player's hand
  if (m_number < 4) {
    m_sprite_posx[0] = 2+64*m_number;
    m_sprite_posy[0] = 4+192+48;
    m_sprite_posx[1] = 2+64*m_number;
    m_sprite_posy[1] = 49+192+48;
  }
  else {
    m_sprite_posx[0] = 2+64*(m_number-4);
    m_sprite_posy[0] = 4+192+48+94;
    m_sprite_posx[1] = 2+64*(m_number-4);
    m_sprite_posy[1] = 49+192+48+94;
  }
}

CCard::~CCard(void) {
  PA_DualDeleteSprite(m_sprite_number[1]);
  PA_DualDeleteSprite(m_sprite_number[0]);
}

void CCard::display(bool visible) {
  // If the card is invisible, display the back of the card
  if (!visible) {
    PA_DualLoadSpritePal(m_palette_number, (void*)card_Pal);
    PA_DualCreateSprite(m_sprite_number[0], (void*)backcard_Sprite,
                        OBJ_SIZE_64X64, 1, m_palette_number,
                        m_sprite_posx[0], m_sprite_posy[0]);
    PA_DualCloneSprite(m_sprite_number[1], m_sprite_number[0]);
    PA_DualSetSpriteVflip(m_sprite_number[1], 1);
    m_sprite_posy[1] = m_sprite_posy[0]+26;
    PA_DualSetSpriteXY(m_sprite_number[1], m_sprite_posx[1], m_sprite_posy[1]);
    PA_DualSetSpritePrio(m_sprite_number[0], 1);
    PA_DualSetSpritePrio(m_sprite_number[1], 1);
    return;
  }
  // Otherwise, Display the card sprites
  switch (m_cardtype) {
    case 0:
      switch (m_cardnumber) {
        case 0:
          PA_DualLoadSpritePal(m_palette_number, (void*)attack1_Pal);
          PA_DualCreateSprite(m_sprite_number[0], (void*)attack1_1_Sprite,
                              OBJ_SIZE_64X64, 1, m_palette_number,
                              m_sprite_posx[0], m_sprite_posy[0]);
          PA_DualCreateSprite(m_sprite_number[1], (void*)attack1_2_Sprite,
                              OBJ_SIZE_64X64, 1, m_palette_number,
                              m_sprite_posx[1], m_sprite_posy[1]);
          break;
        case 1:
          PA_DualLoadSpritePal(m_palette_number, (void*)attack2_Pal);
          PA_DualCreateSprite(m_sprite_number[0], (void*)attack2_1_Sprite,
                              OBJ_SIZE_64X64, 1, m_palette_number,
                              m_sprite_posx[0], m_sprite_posy[0]);
          PA_DualCreateSprite(m_sprite_number[1], (void*)attack2_2_Sprite,
                              OBJ_SIZE_64X64, 1, m_palette_number,
                              m_sprite_posx[1], m_sprite_posy[1]);
          break;
        case 2:
          PA_DualLoadSpritePal(m_palette_number, (void*)attack3_Pal);
          PA_DualCreateSprite(m_sprite_number[0], (void*)attack3_1_Sprite,
                              OBJ_SIZE_64X64, 1, m_palette_number,
                              m_sprite_posx[0], m_sprite_posy[0]);
          PA_DualCreateSprite(m_sprite_number[1], (void*)attack3_2_Sprite,
                              OBJ_SIZE_64X64, 1, m_palette_number,
                              m_sprite_posx[1], m_sprite_posy[1]);
          break;
        case 3:
          PA_DualLoadSpritePal(m_palette_number, (void*)attack4_Pal);
          PA_DualCreateSprite(m_sprite_number[0], (void*)attack4_1_Sprite,
                              OBJ_SIZE_64X64, 1, m_palette_number,
                              m_sprite_posx[0], m_sprite_posy[0]);
          PA_DualCreateSprite(m_sprite_number[1], (void*)attack4_2_Sprite,
                              OBJ_SIZE_64X64, 1, m_palette_number,
                              m_sprite_posx[1], m_sprite_posy[1]);
          break;
        case 4:
          PA_DualLoadSpritePal(m_palette_number, (void*)attack5_Pal);
          PA_DualCreateSprite(m_sprite_number[0], (void*)attack5_1_Sprite,
                              OBJ_SIZE_64X64, 1, m_palette_number,
                              m_sprite_posx[0], m_sprite_posy[0]);
          PA_DualCreateSprite(m_sprite_number[1], (void*)attack5_2_Sprite,
                              OBJ_SIZE_64X64, 1, m_palette_number,
                              m_sprite_posx[1], m_sprite_posy[1]);
          break;
        case 5:
          PA_DualLoadSpritePal(m_palette_number, (void*)attack6_Pal);
          PA_DualCreateSprite(m_sprite_number[0], (void*)attack6_1_Sprite,
                              OBJ_SIZE_64X64, 1, m_palette_number,
                              m_sprite_posx[0], m_sprite_posy[0]);
          PA_DualCreateSprite(m_sprite_number[1], (void*)attack6_2_Sprite,
                              OBJ_SIZE_64X64, 1, m_palette_number,
                              m_sprite_posx[1], m_sprite_posy[1]);
          break;
        case 6:
          PA_DualLoadSpritePal(m_palette_number, (void*)attack7_Pal);
          PA_DualCreateSprite(m_sprite_number[0], (void*)attack7_1_Sprite,
                              OBJ_SIZE_64X64, 1, m_palette_number,
                              m_sprite_posx[0], m_sprite_posy[0]);
          PA_DualCreateSprite(m_sprite_number[1], (void*)attack7_2_Sprite,
                              OBJ_SIZE_64X64, 1, m_palette_number,
                              m_sprite_posx[1], m_sprite_posy[1]);
          break;
        case 7:
          PA_DualLoadSpritePal(m_palette_number, (void*)attack8_Pal);
          PA_DualCreateSprite(m_sprite_number[0], (void*)attack8_1_Sprite,
                              OBJ_SIZE_64X64, 1, m_palette_number,
                              m_sprite_posx[0], m_sprite_posy[0]);
          PA_DualCreateSprite(m_sprite_number[1], (void*)attack8_2_Sprite,
                              OBJ_SIZE_64X64, 1, m_palette_number,
                              m_sprite_posx[1], m_sprite_posy[1]);
          break;
        case 8:
          PA_DualLoadSpritePal(m_palette_number, (void*)attack9_Pal);
          PA_DualCreateSprite(m_sprite_number[0], (void*)attack9_1_Sprite,
                              OBJ_SIZE_64X64, 1, m_palette_number,
                              m_sprite_posx[0], m_sprite_posy[0]);
          PA_DualCreateSprite(m_sprite_number[1], (void*)attack9_2_Sprite,
                              OBJ_SIZE_64X64, 1, m_palette_number,
                              m_sprite_posx[1], m_sprite_posy[1]);
          break;
        case 9:
          PA_DualLoadSpritePal(m_palette_number, (void*)attack10_Pal);
          PA_DualCreateSprite(m_sprite_number[0], (void*)attack10_1_Sprite,
                              OBJ_SIZE_64X64, 1, m_palette_number,
                              m_sprite_posx[0], m_sprite_posy[0]);
          PA_DualCreateSprite(m_sprite_number[1], (void*)attack10_2_Sprite,
                              OBJ_SIZE_64X64, 1, m_palette_number,
                              m_sprite_posx[1], m_sprite_posy[1]);
          break;
        default:
          PA_OutputText(1,0,0,"This card number does not exist.");
          break;
      }
      break;
    case 1:
      switch (m_cardnumber) {
        case 0:
          PA_DualLoadSpritePal(m_palette_number, (void*)defense1_Pal);
          PA_DualCreateSprite(m_sprite_number[0], (void*)defense1_1_Sprite,
                              OBJ_SIZE_64X64, 1, m_palette_number,
                              m_sprite_posx[0], m_sprite_posy[0]);
          PA_DualCreateSprite(m_sprite_number[1], (void*)defense1_2_Sprite,
                              OBJ_SIZE_64X64, 1, m_palette_number,
                              m_sprite_posx[1], m_sprite_posy[1]);
          break;
        case 1:
          PA_DualLoadSpritePal(m_palette_number, (void*)defense2_Pal);
          PA_DualCreateSprite(m_sprite_number[0], (void*)defense2_1_Sprite,
                              OBJ_SIZE_64X64, 1, m_palette_number,
                              m_sprite_posx[0], m_sprite_posy[0]);
          PA_DualCreateSprite(m_sprite_number[1], (void*)defense2_2_Sprite,
                              OBJ_SIZE_64X64, 1, m_palette_number,
                              m_sprite_posx[1], m_sprite_posy[1]);
          break;
        case 2:
          PA_DualLoadSpritePal(m_palette_number, (void*)defense3_Pal);
          PA_DualCreateSprite(m_sprite_number[0], (void*)defense3_1_Sprite,
                              OBJ_SIZE_64X64, 1, m_palette_number,
                              m_sprite_posx[0], m_sprite_posy[0]);
          PA_DualCreateSprite(m_sprite_number[1], (void*)defense3_2_Sprite,
                              OBJ_SIZE_64X64, 1, m_palette_number,
                              m_sprite_posx[1], m_sprite_posy[1]);
          break;
        case 3:
          PA_DualLoadSpritePal(m_palette_number, (void*)defense4_Pal);
          PA_DualCreateSprite(m_sprite_number[0], (void*)defense4_1_Sprite,
                              OBJ_SIZE_64X64, 1, m_palette_number,
                              m_sprite_posx[0], m_sprite_posy[0]);
          PA_DualCreateSprite(m_sprite_number[1], (void*)defense4_2_Sprite,
                              OBJ_SIZE_64X64, 1, m_palette_number,
                              m_sprite_posx[1], m_sprite_posy[1]);
          break;
        case 4:
          PA_DualLoadSpritePal(m_palette_number, (void*)defense5_Pal);
          PA_DualCreateSprite(m_sprite_number[0], (void*)defense5_1_Sprite,
                              OBJ_SIZE_64X64, 1, m_palette_number,
                              m_sprite_posx[0], m_sprite_posy[0]);
          PA_DualCreateSprite(m_sprite_number[1], (void*)defense5_2_Sprite,
                              OBJ_SIZE_64X64, 1, m_palette_number,
                              m_sprite_posx[1], m_sprite_posy[1]);
          break;
        case 5:
          PA_DualLoadSpritePal(m_palette_number, (void*)defense6_Pal);
          PA_DualCreateSprite(m_sprite_number[0], (void*)defense6_1_Sprite,
                              OBJ_SIZE_64X64, 1, m_palette_number,
                              m_sprite_posx[0], m_sprite_posy[0]);
          PA_DualCreateSprite(m_sprite_number[1], (void*)defense6_2_Sprite,
                              OBJ_SIZE_64X64, 1, m_palette_number,
                              m_sprite_posx[1], m_sprite_posy[1]);
          break;
        case 6:
          PA_DualLoadSpritePal(m_palette_number, (void*)defense7_Pal);
          PA_DualCreateSprite(m_sprite_number[0], (void*)defense7_1_Sprite,
                              OBJ_SIZE_64X64, 1, m_palette_number,
                              m_sprite_posx[0], m_sprite_posy[0]);
          PA_DualCreateSprite(m_sprite_number[1], (void*)defense7_2_Sprite,
                              OBJ_SIZE_64X64, 1, m_palette_number,
                              m_sprite_posx[1], m_sprite_posy[1]);
          break;
        case 7:
          PA_DualLoadSpritePal(m_palette_number, (void*)defense8_Pal);
          PA_DualCreateSprite(m_sprite_number[0], (void*)defense8_1_Sprite,
                              OBJ_SIZE_64X64, 1, m_palette_number,
                              m_sprite_posx[0], m_sprite_posy[0]);
          PA_DualCreateSprite(m_sprite_number[1], (void*)defense8_2_Sprite,
                              OBJ_SIZE_64X64, 1, m_palette_number,
                              m_sprite_posx[1], m_sprite_posy[1]);
          break;
        case 8:
          PA_DualLoadSpritePal(m_palette_number, (void*)defense9_Pal);
          PA_DualCreateSprite(m_sprite_number[0], (void*)defense9_1_Sprite,
                              OBJ_SIZE_64X64, 1, m_palette_number,
                              m_sprite_posx[0], m_sprite_posy[0]);
          PA_DualCreateSprite(m_sprite_number[1], (void*)defense9_2_Sprite,
                              OBJ_SIZE_64X64, 1, m_palette_number,
                              m_sprite_posx[1], m_sprite_posy[1]);
          break;
        case 9:
          PA_DualLoadSpritePal(m_palette_number, (void*)defense10_Pal);
          PA_DualCreateSprite(m_sprite_number[0], (void*)defense10_1_Sprite,
                              OBJ_SIZE_64X64, 1, m_palette_number,
                              m_sprite_posx[0], m_sprite_posy[0]);
          PA_DualCreateSprite(m_sprite_number[1], (void*)defense10_2_Sprite,
                              OBJ_SIZE_64X64, 1, m_palette_number,
                              m_sprite_posx[1], m_sprite_posy[1]);
          break;
        default:
          PA_OutputText(1,0,0,"This card number does not exist.");
          break;
      }
      break;
    case 2:
      switch (m_cardnumber) {
        case 0:
          PA_DualLoadSpritePal(m_palette_number, (void*)magic1_Pal);
          PA_DualCreateSprite(m_sprite_number[0], (void*)magic1_1_Sprite,
                              OBJ_SIZE_64X64, 1, m_palette_number,
                              m_sprite_posx[0], m_sprite_posy[0]);
          PA_DualCreateSprite(m_sprite_number[1], (void*)magic1_2_Sprite,
                              OBJ_SIZE_64X64, 1, m_palette_number,
                              m_sprite_posx[1], m_sprite_posy[1]);
          break;
        case 1:
          PA_DualLoadSpritePal(m_palette_number, (void*)magic2_Pal);
          PA_DualCreateSprite(m_sprite_number[0], (void*)magic2_1_Sprite,
                              OBJ_SIZE_64X64, 1, m_palette_number,
                              m_sprite_posx[0], m_sprite_posy[0]);
          PA_DualCreateSprite(m_sprite_number[1], (void*)magic2_2_Sprite, 
                              OBJ_SIZE_64X64, 1, m_palette_number,
                              m_sprite_posx[1], m_sprite_posy[1]);
          break;
        case 2:
          PA_DualLoadSpritePal(m_palette_number, (void*)magic3_Pal);
          PA_DualCreateSprite(m_sprite_number[0], (void*)magic3_1_Sprite, 
                              OBJ_SIZE_64X64, 1, m_palette_number,
                              m_sprite_posx[0], m_sprite_posy[0]);
          PA_DualCreateSprite(m_sprite_number[1], (void*)magic3_2_Sprite,
                              OBJ_SIZE_64X64, 1, m_palette_number,
                              m_sprite_posx[1], m_sprite_posy[1]);
          break;
        case 3:
          PA_DualLoadSpritePal(m_palette_number, (void*)magic4_Pal);
          PA_DualCreateSprite(m_sprite_number[0], (void*)magic4_1_Sprite,
                              OBJ_SIZE_64X64, 1, m_palette_number,
                              m_sprite_posx[0], m_sprite_posy[0]);
          PA_DualCreateSprite(m_sprite_number[1], (void*)magic4_2_Sprite,
                              OBJ_SIZE_64X64, 1, m_palette_number,
                              m_sprite_posx[1], m_sprite_posy[1]);
          break;
        case 4:
          PA_DualLoadSpritePal(m_palette_number, (void*)magic5_Pal);
          PA_DualCreateSprite(m_sprite_number[0], (void*)magic5_1_Sprite,
                              OBJ_SIZE_64X64, 1, m_palette_number, 
                              m_sprite_posx[0], m_sprite_posy[0]);
          PA_DualCreateSprite(m_sprite_number[1], (void*)magic5_2_Sprite,
                              OBJ_SIZE_64X64, 1, m_palette_number,
                              m_sprite_posx[1], m_sprite_posy[1]);
          break;
        case 5:
          PA_DualLoadSpritePal(m_palette_number, (void*)magic6_Pal);
          PA_DualCreateSprite(m_sprite_number[0], (void*)magic6_1_Sprite,
                              OBJ_SIZE_64X64, 1, m_palette_number,
                              m_sprite_posx[0], m_sprite_posy[0]);
          PA_DualCreateSprite(m_sprite_number[1], (void*)magic6_2_Sprite,
                              OBJ_SIZE_64X64, 1, m_palette_number,
                              m_sprite_posx[1], m_sprite_posy[1]);
          break;
        case 6:
          PA_DualLoadSpritePal(m_palette_number, (void*)magic7_Pal);
          PA_DualCreateSprite(m_sprite_number[0], (void*)magic7_1_Sprite,
                              OBJ_SIZE_64X64, 1, m_palette_number,
                              m_sprite_posx[0], m_sprite_posy[0]);
          PA_DualCreateSprite(m_sprite_number[1], (void*)magic7_2_Sprite,
                              OBJ_SIZE_64X64, 1, m_palette_number,
                              m_sprite_posx[1], m_sprite_posy[1]);
          break;
        case 7:
          PA_DualLoadSpritePal(m_palette_number, (void*)magic8_Pal);
          PA_DualCreateSprite(m_sprite_number[0], (void*)magic8_1_Sprite,
                              OBJ_SIZE_64X64, 1, m_palette_number,
                              m_sprite_posx[0], m_sprite_posy[0]);
          PA_DualCreateSprite(m_sprite_number[1], (void*)magic8_2_Sprite,
                              OBJ_SIZE_64X64, 1, m_palette_number,
                              m_sprite_posx[1], m_sprite_posy[1]);
          break;
        case 8:
          PA_DualLoadSpritePal(m_palette_number, (void*)magic9_Pal);
          PA_DualCreateSprite(m_sprite_number[0], (void*)magic9_1_Sprite,
                              OBJ_SIZE_64X64, 1, m_palette_number,
                              m_sprite_posx[0], m_sprite_posy[0]);
          PA_DualCreateSprite(m_sprite_number[1], (void*)magic9_2_Sprite,
                              OBJ_SIZE_64X64, 1, m_palette_number,
                              m_sprite_posx[1], m_sprite_posy[1]);
          break;
        case 9:
          PA_DualLoadSpritePal(m_palette_number, (void*)magic10_Pal);
          PA_DualCreateSprite(m_sprite_number[0], (void*)magic10_1_Sprite,
                              OBJ_SIZE_64X64, 1, m_palette_number,
                              m_sprite_posx[0], m_sprite_posy[0]);
          PA_DualCreateSprite(m_sprite_number[1], (void*)magic10_2_Sprite,
                              OBJ_SIZE_64X64, 1, m_palette_number,
                              m_sprite_posx[1], m_sprite_posy[1]);
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
  // If the card is not playable, set the sprite's mode to alpha blending
  if (!m_isPlayable) {
    PA_DualSetSpriteMode(m_sprite_number[0], 1);
    PA_DualSetSpriteMode(m_sprite_number[1], 1);
  }
  PA_DualSetSpritePrio(m_sprite_number[0], 1);
  PA_DualSetSpritePrio(m_sprite_number[1], 1);
}

void CCard::hide(void) {
  PA_DualDeleteSprite(m_sprite_number[1]);
  PA_DualDeleteSprite(m_sprite_number[0]);
}

bool CCard::isTouched() {
  u16 posX, posY;
  if (Stylus.Newpress) {
    posX = Stylus.X;
    posY = Stylus.Y+192+48;
    return ((posX > m_sprite_posx[0]) && (posX < m_sprite_posx[0]+60) &&
            (posY > m_sprite_posy[0]) && (posY < m_sprite_posy[0]+90));
  }
  else
    return false;
}

void CCard::moveCardOnDeck(const int p_cardSpeed, bool visible) {
  int dx = 129 - m_sprite_posx[0];
  int dy = 1 - m_sprite_posy[0];
  PA_16cErase(0);
  if (!visible) {  // If the card is invisible, hide the current back sprites
                   // and display the card sprites
    hide();
    if (m_number < 4)
      m_sprite_posy[1] = 49+192+48;
    else
      m_sprite_posy[1] = 49+192+48+94;
    display(true);
  }
  PA_DualSetSpriteMode(m_sprite_number[0], 0);
  PA_DualSetSpriteMode(m_sprite_number[1], 0);
  PA_DualSetSpritePrio(m_sprite_number[0], 0);
  PA_DualSetSpritePrio(m_sprite_number[1], 0);
  // Move the card frm the player's hand to the deck
  float m = (float) dy / (float) dx;  // compute slope
	float b = m_sprite_posy[0] - m*m_sprite_posx[0];
	dx = (dx < 0) ? -1 : 1;
	int count = 0;
	while (m_sprite_posx[0] != 129) {
    m_sprite_posx[0] += dx;
    m_sprite_posx[1] += dx;
    dy = round(m*m_sprite_posx[0] + b) - m_sprite_posy[0];
    dy = (dy < 0) ? -1 : 1;
    while (m_sprite_posy[0] != round(m*m_sprite_posx[0] + b)) {
      m_sprite_posy[0] += dy;
      m_sprite_posy[1] += dy;
      PA_DualSetSpriteXY(m_sprite_number[0], m_sprite_posx[0],
                         m_sprite_posy[0]);
      PA_DualSetSpriteXY(m_sprite_number[1], m_sprite_posx[1],
                         m_sprite_posy[1]);
      count++;
      if (count > p_cardSpeed) { PA_WaitForVBL(); count = 0; }
    }
	}
}

void CCard::moveCardFromDeck(const int p_cardSpeed, bool visible) {
  int dx = m_sprite_posx[0] - 67;
  int dy = m_sprite_posy[0] - 1;
  int posx[2], posy[2];
  // Save the card position in the player's hand
  posx[0] = m_sprite_posx[0];
  posx[1] = m_sprite_posx[1];
  posy[0] = m_sprite_posy[0];
  posy[1] = m_sprite_posy[1];
  // Set the current card position to the deck position
  m_sprite_posx[0] = 67;
  m_sprite_posy[0] = 1;
  m_sprite_posx[1] = 67;
  m_sprite_posy[1] = 1+45;
  // Display the card on the deck
  display(visible);
  PA_DualSetSpriteMode(m_sprite_number[0], 0);
  PA_DualSetSpriteMode(m_sprite_number[1], 0);
  PA_DualSetSpritePrio(m_sprite_number[0], 0);
  PA_DualSetSpritePrio(m_sprite_number[1], 0);
  // Move the card from the deck to the player's hand
	float m = (float) dy / (float) dx;  // compute slope
	float b = m_sprite_posy[0] - m*m_sprite_posx[0];
	dx = (dx < 0) ? -1 : 1;
	int count = 0;
	while (m_sprite_posx[0] != posx[0]) {
    m_sprite_posx[0] += dx;
    m_sprite_posx[1] += dx;
    dy = round(m*m_sprite_posx[0] + b) - m_sprite_posy[0];
    dy = (dy < 0) ? -1 : 1;
    while (m_sprite_posy[0] != round(m*m_sprite_posx[0] + b)) {
      m_sprite_posy[0] += dy;
      m_sprite_posy[1] += dy;
      PA_DualSetSpriteXY(m_sprite_number[0], m_sprite_posx[0],
                         m_sprite_posy[0]);
      PA_DualSetSpriteXY(m_sprite_number[1], m_sprite_posx[1],
                         m_sprite_posy[1]);
      count++;
      if (count > p_cardSpeed) { PA_WaitForVBL(); count = 0; }
    }
	}
  PA_DualSetSpritePrio(m_sprite_number[0], 1);
  PA_DualSetSpritePrio(m_sprite_number[1], 1);
	if ((!m_isPlayable) && (visible)) {
    PA_DualSetSpriteMode(m_sprite_number[0], 1);
    PA_DualSetSpriteMode(m_sprite_number[1], 1);
  }
}

void CCard::setDiscard(const bool pdiscard) {
  m_discard = pdiscard;
  if (m_discard) {  // If the discard mode is activated, display "Discard"
                    // on top of the card
    PA_DualSetSpriteMode(m_sprite_number[0], 1);
    PA_DualSetSpriteMode(m_sprite_number[1], 1);
    if (m_number < 4)
      PA_16cText(0, 5+m_number*64, 50, 255, 40, "Discard", TEXT_RED+1, 3, 100);
    else
      PA_16cText(0, 5+(m_number-4)*64, 50+94, 255, 90, "Discard", TEXT_RED+1, 3,
                 100);
  }
  else {
    PA_16cErase (0);
    PA_SetSFXAlpha(0,	7, 15);
    if (m_isPlayable) {
      PA_DualSetSpriteMode(m_sprite_number[0], 0);
      PA_DualSetSpriteMode(m_sprite_number[1], 0);
    }
  }
}
