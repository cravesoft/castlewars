#include "COptions.h"

// Gfx
#include "gfx/optionsresume.pal.c"
#include "gfx/optionsresume.c"
#include "gfx/optionsmusic.pal.c"
#include "gfx/optionsmusic.c"
#include "gfx/optionsspeed.pal.c"
#include "gfx/optionsspeed.c"
#include "gfx/optionsyes.pal.c"
#include "gfx/optionsyes.c"
#include "gfx/optionsno.pal.c"
#include "gfx/optionsno.c"
#include "gfx/item.c"

COptions::COptions(void) : m_itemTouched(0) {}

COptions::~COptions(void) {}

bool COptions::display(int *p_musicVolume, int *p_cardSpeed) {
  // Display the options menu with the resume button selected
  PA_EasyBgLoad(0, 2, optionsresume);
  // Set the values for the music volume and card speed
  // with the function parameters 
  m_musicVolume = *p_musicVolume;
  m_cardSpeed = *p_cardSpeed;
  // Display the item sprite at the position that corresponds to the current
  // music volume 
  switch (m_musicVolume) {
    case 0:
      PA_CreateSprite(0, INDEX_SPRITE_NB_ITEM_MUSIC, (void*)item_Sprite,
                      OBJ_SIZE_32X32, 1, PALETTE_NB_ITEM, 137, 52);
      break;
    case 60:
      PA_CreateSprite(0, INDEX_SPRITE_NB_ITEM_MUSIC, (void*)item_Sprite,
                      OBJ_SIZE_32X32, 1, PALETTE_NB_ITEM, 176, 52);
      break;
    case 127:
      PA_CreateSprite(0, INDEX_SPRITE_NB_ITEM_MUSIC, (void*)item_Sprite,
                      OBJ_SIZE_32X32, 1, PALETTE_NB_ITEM, 213, 52);
      break;
    default:
      PA_CreateSprite(0, INDEX_SPRITE_NB_ITEM_MUSIC, (void*)item_Sprite,
                      OBJ_SIZE_32X32, 1, PALETTE_NB_ITEM, 176, 52);
      break;
  }
  // Clone the music volume item sprite to get the card speed item sprite
  PA_CloneSprite(0, INDEX_SPRITE_NB_ITEM_SPEED, INDEX_SPRITE_NB_ITEM_MUSIC);
  // Display the cloned item sprite at the position that corresponds
  // to the current card speed 
  switch (m_cardSpeed) {
    case 5:
      PA_SetSpriteXY(0, INDEX_SPRITE_NB_ITEM_SPEED, 137, 99);
      break;
    case 10:
      PA_SetSpriteXY(0, INDEX_SPRITE_NB_ITEM_SPEED, 176, 99);
      break;
    case 20:
      PA_SetSpriteXY(0, INDEX_SPRITE_NB_ITEM_SPEED, 213, 99);
      break;
    default:
      PA_SetSpriteXY(0, INDEX_SPRITE_NB_ITEM_SPEED, 176, 99);
      break;
  }
  // Set the item sprites mode to alpha blending
  PA_SetSpriteMode(0, INDEX_SPRITE_NB_ITEM_MUSIC, 1);
  PA_SetSpriteMode(0, INDEX_SPRITE_NB_ITEM_SPEED, 1);
  // Change the background to the corresponding player's action
  m_itemTouched = -1;
  PA_WaitForVBL();
  while (!Pad.Newpress.Start) {
    m_itemTouched = itemTouched();  // Perform the action and return the
                                    // player's selection
    switch(m_itemTouched) {
      case 1:
        PA_EasyBgLoad(0, 1, optionsresume);
        break;
      case 2:
        PA_EasyBgLoad(0, 1, optionsmusic);
        break;
      case 3:
        PA_EasyBgLoad(0, 1, optionsspeed);
        break;
      case 4:
        PA_EasyBgLoad(0, 1, optionsno);
        break;
      case 5:
        PA_EasyBgLoad(0, 1, optionsno);
        break;
      case 6:
        PA_EasyBgLoad(0, 1, optionsyes);
        break;
      default:
        break;
    }
    // Quit the loop if the player chooses to resume or quit the game
    if ((m_itemTouched == 1) || (m_itemTouched == 5) || (m_itemTouched == 6))
      break;
    PA_WaitForVBL();
  }
  // Delete the item sprites
  PA_DeleteSprite(0, INDEX_SPRITE_NB_ITEM_SPEED);
  PA_DeleteSprite(0, INDEX_SPRITE_NB_ITEM_MUSIC);
  // Retrieve the music volume and card speed
  *p_musicVolume = m_musicVolume;
  *p_cardSpeed = m_cardSpeed;
  // Return the state of the game
  switch(m_itemTouched) {
    case 0:  // Resume the game
      return false;
      break;
    case 5:  // Resume the game
      return false;
      break;
    case 6:  // Quit the game
      return true;
      break;
    default:
      break;
  }
  return false;
}

u16 COptions::itemTouched() {
  u16 posX, posY;
  if (Stylus.Released) {
    posX = Stylus.X;
    posY = Stylus.Y;
    if ((posX > 9) && (posX < 78) && (posY > 13) && (posY < 34)) return 1;
    if ((posX > 8) && (posX < 124) && (posY > 58) && (posY < 82)) return 2;
    if ((posX > 7) && (posX < 107) && (posY > 107) && (posY < 136)) return 3;
    if ((posX > 9) && (posX < 97) && (posY > 155) && (posY < 182)) return 4;
    if ((posX > 137) && (posX < 137+32) && (posY > 52) && (posY < 52+32)) {
      m_musicVolume = 0;
      AS_SetMP3Volume(m_musicVolume);
      PA_SetSpriteXY(0, INDEX_SPRITE_NB_ITEM_MUSIC, 137, 52);
      return m_itemTouched;
    }
    if ((posX > 176) && (posX < 176+32) && (posY > 52) && (posY < 52+32)) {
      m_musicVolume = 60;
      AS_SetMP3Volume(m_musicVolume);
      PA_SetSpriteXY(0, INDEX_SPRITE_NB_ITEM_MUSIC, 176, 52);
      return m_itemTouched;
    }
    if ((posX > 213) && (posX < 213+32) && (posY > 52) && (posY < 52+32)) {
      m_musicVolume = 127;
      AS_SetMP3Volume(m_musicVolume);
      PA_SetSpriteXY(0, INDEX_SPRITE_NB_ITEM_MUSIC, 213, 52);
      return m_itemTouched;
    }
    if ((posX > 137) && (posX < 137+32) && (posY > 99) && (posY < 99+32)) {
      m_cardSpeed = 5;
      PA_SetSpriteXY(0, INDEX_SPRITE_NB_ITEM_SPEED, 137, 99);
      return m_itemTouched;
    }
    if ((posX > 176) && (posX < 176+32) && (posY > 99) && (posY < 99+32)) {
      m_cardSpeed = 10;
      PA_SetSpriteXY(0, INDEX_SPRITE_NB_ITEM_SPEED, 176, 99);
      return m_itemTouched;
    }
    if ((posX > 213) && (posX < 213+32) && (posY > 99) && (posY < 99+32)) {
      m_cardSpeed = 20;
      PA_SetSpriteXY(0, INDEX_SPRITE_NB_ITEM_SPEED, 213, 99);
      return m_itemTouched;
    }
    if (m_itemTouched == 4) {
      if ((posX > 193) && (posX < 221) && (posY > 157) && (posY < 176))
        return 5;
      if ((posX > 142) && (posX < 173) && (posY > 157) && (posY < 176))
        return 6;
      return 4;
    }
    return m_itemTouched;
  }
  else
    return m_itemTouched;
}
