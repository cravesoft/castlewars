#include "CPlayer2.h"

// Gfx
#include "gfx/topcastle.c"
#include "gfx/castle.c"
#include "gfx/wall.c"

CPlayer2::CPlayer2(void) {
  // Display the castle and the wall
  PA_CreateSprite(1, SPRITE_NB_CASTLE2_PART1, (void*)topcastle_Sprite,
                  OBJ_SIZE_64X64, 1, PALETTE_NB_CASTLE, 151, 192-m_castle);
  PA_CreateSprite(1, SPRITE_NB_CASTLE2_PART2, (void*)castle_Sprite,
                  OBJ_SIZE_64X64, 1, PALETTE_NB_CASTLE,
                  151+256, 192+64-m_castle); 
  PA_CreateSprite(1, SPRITE_NB_WALL2_PART1, (void*)wall_Sprite,
                  OBJ_SIZE_8X32, 1, PALETTE_NB_CASTLE, 142, 192-m_wall);
  PA_CloneSprite(1, SPRITE_NB_WALL2_PART2, SPRITE_NB_WALL1_PART1);
  PA_SetSpriteXY(1, SPRITE_NB_WALL2_PART2, 142+256, 192+28-m_wall);
  PA_CloneSprite(1, SPRITE_NB_WALL2_PART3, SPRITE_NB_WALL1_PART1);
  PA_SetSpriteXY(1, SPRITE_NB_WALL2_PART3, 142+256, 192+28+28-m_wall);
  PA_CloneSprite(1, SPRITE_NB_WALL2_PART4, SPRITE_NB_WALL1_PART1);
  PA_SetSpriteXY(1, SPRITE_NB_WALL2_PART4, 142+256, 192+28+28+28-m_wall);
  PA_SetSpritePrio (1, SPRITE_NB_CASTLE2_PART1, 2);
  PA_SetSpritePrio (1, SPRITE_NB_CASTLE2_PART2, 2);
  PA_SetSpritePrio (1, SPRITE_NB_WALL2_PART1, 2);
  PA_SetSpritePrio (1, SPRITE_NB_WALL2_PART2, 2);
  PA_SetSpritePrio (1, SPRITE_NB_WALL2_PART3, 2);
  PA_SetSpritePrio (1, SPRITE_NB_WALL2_PART4, 2);
}

CPlayer2::~CPlayer2(void) {
  PA_DeleteSprite(1, SPRITE_NB_CASTLE2_PART1);
  PA_DeleteSprite(1, SPRITE_NB_CASTLE2_PART2);
  PA_DeleteSprite(1, SPRITE_NB_WALL2_PART1);
  PA_DeleteSprite(1, SPRITE_NB_WALL2_PART2);
  PA_DeleteSprite(1, SPRITE_NB_WALL2_PART3);
  PA_DeleteSprite(1, SPRITE_NB_WALL2_PART4);
}

void CPlayer2::reset(void) {
  PA_SetSpriteXY(1, SPRITE_NB_CASTLE2_PART1, 151, 192-m_castle);
  PA_SetSpriteXY(1, SPRITE_NB_CASTLE2_PART2, 151+256, 192+64-m_castle);
  PA_SetSpriteXY(1, SPRITE_NB_WALL2_PART1, 142, 192-m_wall);
  PA_SetSpriteXY(1, SPRITE_NB_WALL2_PART2, 142+256, 192+28-m_wall);
  PA_SetSpriteXY(1, SPRITE_NB_WALL2_PART3, 142+256, 192+28+28-m_wall);
  PA_SetSpriteXY(1, SPRITE_NB_WALL2_PART4, 142+256, 192+28+28+28-m_wall);
}

void CPlayer2::displayStats() {
  // Update the player's statistics
  CPlayer::displayStats();
  // Display in yellow the number of material the player gets at each turn
  // and the castle's height  
  PA_SetTextTileCol(1, TEXT_YELLOW);
	if (m_defensev < 10)
	 PA_OutputText(1,28,1,"  %d",m_defensev);
	else if (m_defensev < 100)
	 PA_OutputText(1,28,1," %d",m_defensev);
	else
	 PA_OutputText(1,28,1,"%d",m_defensev);
  if (m_attackv < 10)
	 PA_OutputText(1,28,7,"  %d",m_attackv);
	else if (m_attackv < 100)
	 PA_OutputText(1,28,7," %d",m_attackv);
	else
	 PA_OutputText(1,28,7,"%d",m_attackv);
	if (m_magicv < 10)
	 PA_OutputText(1,28,13,"  %d",m_magicv);
	else if (m_magicv < 100)
	 PA_OutputText(1,28,13," %d",m_magicv);
	else
	 PA_OutputText(1,28,13,"%d",m_magicv);
	if (m_castle < 10)
	 PA_OutputText(1,28,19,"  %d",m_castle);
	else if (m_castle < 100)
	 PA_OutputText(1,28,19," %d",m_castle);
	else
	 PA_OutputText(1,28,19,"%d",m_castle);
	// Display in white the number of material the player has
  // and the wall's height
	PA_SetTextTileCol(1, TEXT_WHITE);
	if (m_defense < 10)
	 PA_OutputText(1,28,4,"  %d",m_defense);
	else if (m_defense < 100)
	 PA_OutputText(1,28,4," %d",m_defense);
	else
	 PA_OutputText(1,28,4,"%d",m_defense);
  if (m_attack < 10)
	 PA_OutputText(1,28,10,"  %d",m_attack);
	else if (m_attack < 100)
	 PA_OutputText(1,28,10," %d",m_attack);
	else
	 PA_OutputText(1,28,10,"%d",m_attack);
	if (m_magic < 10)
	 PA_OutputText(1,28,16,"  %d",m_magic);
	else if (m_magic < 100)
	 PA_OutputText(1,28,16," %d",m_magic);
	else
	 PA_OutputText(1,28,16,"%d",m_magic);
	if (m_wall < 10)
	 PA_OutputText(1,28,22,"  %d",m_wall);
	else if (m_wall < 100)
	 PA_OutputText(1,28,22," %d",m_wall);
	else
	 PA_OutputText(1,28,22,"%d",m_wall);
}

void CPlayer2::hideStats() {	
  PA_OutputText(1,28,1,"   ");
  PA_OutputText(1,28,7,"   ");
  PA_OutputText(1,28,13,"   ");
  PA_OutputText(1,28,19,"   ");
  PA_OutputText(1,28,4,"   ");
  PA_OutputText(1,28,10,"   ");
  PA_OutputText(1,28,16,"   ");
  PA_OutputText(1,28,22,"   ");
}

void CPlayer2::displayCastle(void) {
  PA_SetSpriteXY(1, SPRITE_NB_CASTLE2_PART1, 151, 192-m_castle);
  if (m_castle > 64)
    PA_SetSpriteXY(1, SPRITE_NB_CASTLE2_PART2, 151, 192+64-m_castle);
  else
    PA_SetSpriteXY(1, SPRITE_NB_CASTLE2_PART2, 151+256, 192+64-m_castle);
  PA_SetSpriteXY(1, SPRITE_NB_WALL2_PART1, 142, 192-m_wall);
  if (m_wall > 28) {
    PA_SetSpriteXY(1, SPRITE_NB_WALL2_PART2, 142, 192+28-m_wall);
    if (m_wall > 28+28) {
      PA_SetSpriteXY(1, SPRITE_NB_WALL2_PART3, 142, 192+28+28-m_wall);
      if (m_wall > 28+28+28)
        PA_SetSpriteXY(1, SPRITE_NB_WALL2_PART4, 142, 192+28+28+28-m_wall);
      else
        PA_SetSpriteXY(1, SPRITE_NB_WALL2_PART4, 142+256, 192+28+28+28-m_wall);
    } else {
      PA_SetSpriteXY(1, SPRITE_NB_WALL2_PART3, 142+256, 192+28+28-m_wall);
      PA_SetSpriteXY(1, SPRITE_NB_WALL2_PART4, 142+256, 192+28+28+28-m_wall);
    }
  } else {
    PA_SetSpriteXY(1, SPRITE_NB_WALL2_PART2, 142+256, 192+28-m_wall);
    PA_SetSpriteXY(1, SPRITE_NB_WALL2_PART3, 142+256, 192+28+28-m_wall);
    PA_SetSpriteXY(1, SPRITE_NB_WALL2_PART4, 142+256, 192+28+28+28-m_wall);
  }
}

void CPlayer2::hideCastle(void) {
  PA_DeleteSprite(1, SPRITE_NB_CASTLE2_PART1);
  PA_DeleteSprite(1, SPRITE_NB_CASTLE2_PART2);
  PA_DeleteSprite(1, SPRITE_NB_WALL2_PART1);
  PA_DeleteSprite(1, SPRITE_NB_WALL2_PART2);
  PA_DeleteSprite(1, SPRITE_NB_WALL2_PART3);
  PA_DeleteSprite(1, SPRITE_NB_WALL2_PART4);
}

void CPlayer2::displayChanges(void) {
  char str[3];
  ostringstream number;
  if (m_defensevc != 0) {
    memset(str, 0, sizeof (str));
    number.str("");
    if (ABS(m_defensevc) < 10) number << " ";
    if (m_defensevc > 0) {
      number << "+" << ABS(m_defensevc);
      strncpy (str, number.str().c_str(), 3);
      if (ABS(m_defensevc) < 10)
        PA_16cText(1, 178, 9, 255, 7+7, str, 3, 0, 100);
      else
        PA_16cText(1, 175, 9, 255, 7+7, str, 3, 0, 100);
    } else {
      number << "-" << ABS(m_defensevc);
      strncpy (str, number.str().c_str(), 3);
      if (ABS(m_defensevc) < 10)
        PA_16cText(1, 178, 9, 255, 9+2, str, 2, 0, 100);
      else
        PA_16cText(1, 175, 9, 255, 9+2, str, 2, 0, 100);
    }
  }
  if (m_attackvc != 0) {
    memset(str, 0, sizeof(str));
    number.str("");
    if (ABS(m_attackvc) < 10) number << " ";
    if (m_attackvc > 0) {
      number << "+" << ABS(m_attackvc);
      strncpy (str, number.str().c_str(), 3);
      if (ABS(m_attackvc) < 10)
        PA_16cText(1, 178, 9+48, 255, 9+48+2, str, 3, 0, 100);
      else
        PA_16cText(1, 175, 9+48, 255, 9+48+2, str, 3, 0, 100);
    } else {
      number << "-" << ABS(m_attackvc);
      strncpy (str, number.str().c_str(), 3);
      if (ABS(m_attackvc) < 10)
        PA_16cText(1, 178, 9+48, 255, 9+48+2, str, 2, 0, 100);
      else
        PA_16cText(1, 175, 9+48, 255, 9+48+2, str, 2, 0, 100);
    }
  }
  if (m_magicvc != 0) {
    memset(str, 0, sizeof(str));
    number.str("");
    if (ABS(m_magicvc) < 10) number << " ";
    if (m_magicvc > 0) {
      number << "+" << ABS(m_magicvc);
      strncpy (str, number.str().c_str(), 3);
      if (ABS(m_magicvc) < 10)
        PA_16cText(1, 178, 9+48+48, 255, 9+48+48+2, str, 3, 0, 100);
      else
        PA_16cText(1, 175, 9+48+48, 255, 9+48+48+2, str, 3, 0, 100);
    } else {
      number << "-" << ABS(m_magicvc);
      strncpy (str, number.str().c_str(), 3);
      if (ABS(m_magicvc) < 10)
        PA_16cText(1, 178, 9+48+48, 255, 9+48+48+2, str, 2, 0, 100);
      else
        PA_16cText(1, 175, 9+48+48, 255, 9+48+48+2, str, 2, 0, 100);
    }
  }
  if (m_castlec != 0) {
    memset(str, 0, sizeof(str));
    number.str("");
    if (ABS(m_castlec) < 10) number << " ";
    if (m_castlec > 0) {
      number << "+" << ABS(m_castlec);
      strncpy (str, number.str().c_str(), 3);
      if (ABS(m_castlec) < 10)
        PA_16cText(1, 178, 9+48+48+48, 255, 9+48+48+48+2, str, 3, 0, 100);
      else
        PA_16cText(1, 175, 9+48+48+48, 255, 9+48+48+48+2, str, 3, 0, 100);
    } else {
      number << "-" << ABS(m_castlec);
      strncpy (str, number.str().c_str(), 3);
      if (ABS(m_castlec) < 10)
        PA_16cText(1, 178, 9+48+48+48, 255, 9+48+48+48+2, str, 2, 0, 100);
      else
        PA_16cText(1, 175, 9+48+48+48, 255, 9+48+48+48+2, str, 2, 0, 100);
    }
  }
  if (m_defensec != 0) {
    memset(str, 0, sizeof(str));
    number.str("");
    if (ABS(m_defensec) < 10) number << " ";
    if (m_defensec > 0) {
      number << "+" << ABS(m_defensec);
      strncpy (str, number.str().c_str(), 3);
      if (ABS(m_defensec) < 10)
        PA_16cText(1, 178, 9+24, 255, 9+24+2, str, 3, 0, 100);
      else
        PA_16cText(1, 175, 9+24, 255, 9+24+2, str, 3, 0, 100);
    } else {
      number << "-" << ABS(m_defensec);
      strncpy (str, number.str().c_str(), 3);
      if (ABS(m_defensec) < 10)
        PA_16cText(1, 178, 9+24, 255, 9+24+2, str, 2, 0, 100);
      else
        PA_16cText(1, 175, 9+24, 255, 9+24+2, str, 2, 0, 100);
    }
  }
  if (m_attackc != 0) {
    memset(str, 0, sizeof(str));
    number.str("");
    if (ABS(m_attackc) < 10) number << " ";
    if (m_attackc > 0) {
      number << "+" << ABS(m_attackc);
      strncpy (str, number.str().c_str(), 3);
      if (ABS(m_attackc) < 10)
        PA_16cText(1, 178, 9+24+48, 255, 9+24+48+2, str, 3, 0, 100);
      else
        PA_16cText(1, 175, 9+24+48, 255, 9+24+48+2, str, 3, 0, 100);
    } else {
      number << "-" << ABS(m_attackc);
      strncpy (str, number.str().c_str(), 3);
      if (ABS(m_attackc) < 10)
        PA_16cText(1, 178, 9+24+48, 255, 9+24+48+2, str, 2, 0, 100);
      else
        PA_16cText(1, 175, 9+24+48, 255, 9+24+48+2, str, 2, 0, 100);
    }
  }
  if (m_magicc != 0) {
    memset(str, 0, sizeof(str));
    number.str("");
    if (ABS(m_magicc) < 10) number << " ";
    if (m_magicc > 0) {
      number << "+" << ABS(m_magicc);
      strncpy (str, number.str().c_str(), 3);
      if (ABS(m_magicc) < 10)
        PA_16cText(1, 178, 9+24+48+48, 255, 9+24+48+48+2, str, 3, 0, 100);
      else
        PA_16cText(1, 175, 9+24+48+48, 255, 9+24+48+48+2, str, 3, 0, 100);
    } else {
      number << "-" << ABS(m_magicc);
      strncpy (str, number.str().c_str(), 3);
      if (ABS(m_magicc) < 10)
        PA_16cText(1, 178, 9+24+48+48, 255, 9+24+48+48+2, str, 2, 0, 100);
      else
        PA_16cText(1, 175, 9+24+48+48, 255, 9+24+48+48+2, str, 2, 0, 100);
    }
  }
  if (m_wallc != 0) {
    memset(str, 0, sizeof(str));
    number.str("");
    if (ABS(m_wallc) < 10) number << " ";
    if (m_wallc > 0) {
      number << "+" << ABS(m_wallc);
      strncpy (str, number.str().c_str(), 3);
      if (ABS(m_wallc) < 10)
        PA_16cText(1, 178, 9+24+48+48+48, 255, 9+24+48+48+48+2, str, 3, 0, 100);
      else
        PA_16cText(1, 175, 9+24+48+48+48, 255, 9+24+48+48+48+2, str, 3, 0, 100);
    } else {
      number << "-" << ABS(m_wallc);
      strncpy (str, number.str().c_str(), 3);
      if (ABS(m_wallc) < 10)
        PA_16cText(1, 178, 9+24+48+48+48, 255, 9+24+48+48+48+2, str, 2, 0, 100);
      else
        PA_16cText(1, 175, 9+24+48+48+48, 255, 9+24+48+48+48+2, str, 2, 0, 100);
    }
  }
}
