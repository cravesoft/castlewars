#include "CPlayer1.h"

// Gfx
#include "gfx/topcastle.c"
#include "gfx/castle.c"
#include "gfx/wall.c"

CPlayer1::CPlayer1(void) {
  // Display the castle and the wall
  PA_CreateSprite(1, SPRITE_NB_CASTLE1_PART1, (void*)topcastle_Sprite,
                  OBJ_SIZE_64X64, 1, PALETTE_NB_CASTLE, 69, 192-m_castle);
  PA_CreateSprite(1, SPRITE_NB_CASTLE1_PART2, (void*)castle_Sprite,
                  OBJ_SIZE_64X64, 1, PALETTE_NB_CASTLE,
                  69+256, 192+64-m_castle); 
  PA_CreateSprite(1, SPRITE_NB_WALL1_PART1, (void*)wall_Sprite, OBJ_SIZE_8X32,
                  1, PALETTE_NB_CASTLE, 110, 192-m_wall);
  PA_CloneSprite(1, SPRITE_NB_WALL1_PART2, SPRITE_NB_WALL1_PART1);
  PA_SetSpriteXY(1, SPRITE_NB_WALL1_PART2, 110+256, 192+28-m_wall);
  PA_CloneSprite(1, SPRITE_NB_WALL1_PART3, SPRITE_NB_WALL1_PART1);
  PA_SetSpriteXY(1, SPRITE_NB_WALL1_PART3, 110+256, 192+28+28-m_wall);
  PA_CloneSprite(1, SPRITE_NB_WALL1_PART4, SPRITE_NB_WALL1_PART1);
  PA_SetSpriteXY(1, SPRITE_NB_WALL1_PART4, 110+256, 192+28+28+28-m_wall);
  PA_SetSpritePrio (1, SPRITE_NB_CASTLE1_PART1, 2);
  PA_SetSpritePrio (1, SPRITE_NB_CASTLE1_PART2, 2);
  PA_SetSpritePrio (1, SPRITE_NB_WALL1_PART1, 2);
  PA_SetSpritePrio (1, SPRITE_NB_WALL1_PART2, 2);
  PA_SetSpritePrio (1, SPRITE_NB_WALL1_PART3, 2);
  PA_SetSpritePrio (1, SPRITE_NB_WALL1_PART4, 2);
}

CPlayer1::~CPlayer1(void) { 
  PA_DeleteSprite(1, SPRITE_NB_CASTLE1_PART1);
  PA_DeleteSprite(1, SPRITE_NB_CASTLE1_PART2);
  PA_DeleteSprite(1, SPRITE_NB_WALL1_PART1);
  PA_DeleteSprite(1, SPRITE_NB_WALL1_PART2);
  PA_DeleteSprite(1, SPRITE_NB_WALL1_PART3);
  PA_DeleteSprite(1, SPRITE_NB_WALL1_PART4);
}

void CPlayer1::reset(void) {
  PA_SetSpriteXY(1, SPRITE_NB_CASTLE1_PART1, 69, 192-m_castle);
  PA_SetSpriteXY(1, SPRITE_NB_CASTLE1_PART2, 69+256, 192+64-m_castle);
  PA_SetSpriteXY(1, SPRITE_NB_WALL1_PART1, 110, 192-m_wall);
  PA_SetSpriteXY(1, SPRITE_NB_WALL1_PART2, 110+256, 192+28-m_wall);
  PA_SetSpriteXY(1, SPRITE_NB_WALL1_PART3, 110+256, 192+28+28-m_wall);
  PA_SetSpriteXY(1, SPRITE_NB_WALL1_PART4, 110+256, 192+28+28+28-m_wall);
}

void CPlayer1::displayStats() {
  // Update the player's statistics
  CPlayer::displayStats();
  // Display in yellow the number of material the player gets at each turn
  // and the castle's height
  PA_SetTextTileCol(1, TEXT_YELLOW);
  if (m_defensev < 10)
	 PA_OutputText(1,4,1,"  %d",m_defensev);
	else if (m_defensev < 100)
	 PA_OutputText(1,4,1," %d",m_defensev);
	else
	 PA_OutputText(1,4,1,"%d",m_defensev);
	if (m_attackv < 10)
	 PA_OutputText(1,4,7,"  %d",m_attackv);
	else if (m_attackv < 100)
	 PA_OutputText(1,4,7," %d",m_attackv);
	else
	 PA_OutputText(1,4,7,"%d",m_attackv);
	if (m_magicv < 10)
	 PA_OutputText(1,4,13,"  %d",m_magicv);
	else if (m_magicv < 100)
	 PA_OutputText(1,4,13," %d",m_magicv);
	else
	 PA_OutputText(1,4,13,"%d",m_magicv);
	if (m_castle < 10)
	 PA_OutputText(1,4,19,"  %d",m_castle);
	else if (m_castle < 100)
	 PA_OutputText(1,4,19," %d",m_castle);
	else
	 PA_OutputText(1,4,19,"%d",m_castle);
  // Display in white the number of material the player has
  // and the wall's height
	PA_SetTextTileCol(1, TEXT_WHITE);
  if (m_defense < 10)
	 PA_OutputText(1,4,4,"  %d",m_defense);
	else if (m_defense < 100)
	 PA_OutputText(1,4,4," %d",m_defense);
	else
	 PA_OutputText(1,4,4,"%d",m_defense);
  if (m_attack < 10)
	 PA_OutputText(1,4,10,"  %d",m_attack);
	else if (m_attack < 100)
	 PA_OutputText(1,4,10," %d",m_attack);
	else
	 PA_OutputText(1,4,10,"%d",m_attack);
	if (m_magic < 10)
	 PA_OutputText(1,4,16,"  %d",m_magic);
	else if (m_magic < 100)
	 PA_OutputText(1,4,16," %d",m_magic);
	else
	 PA_OutputText(1,4,16,"%d",m_magic);
	if (m_wall < 10)
	 PA_OutputText(1,4,22,"  %d",m_wall);
	else if (m_wall < 100)
	 PA_OutputText(1,4,22," %d",m_wall);
	else
	 PA_OutputText(1,4,22,"%d",m_wall);
}

void CPlayer1::hideStats() {	
  PA_OutputText(1,4,1,"   ");
  PA_OutputText(1,4,7,"   ");
  PA_OutputText(1,4,13,"   ");
  PA_OutputText(1,4,19,"   ");
  PA_OutputText(1,4,4,"   ");
  PA_OutputText(1,4,10,"   ");
  PA_OutputText(1,4,16,"   ");
  PA_OutputText(1,4,22,"   ");
}

void CPlayer1::displayCastle(void) {
  PA_SetSpriteXY(1, SPRITE_NB_CASTLE1_PART1, 69, 192-m_castle);
  if (m_castle > 64)
    PA_SetSpriteXY(1, SPRITE_NB_CASTLE1_PART2, 69, 192+64-m_castle);
  else
    PA_SetSpriteXY(1, SPRITE_NB_CASTLE1_PART2, 69+256, 192+64-m_castle);
  PA_SetSpriteXY(1, SPRITE_NB_WALL1_PART1, 110, 192-m_wall);
  if (m_wall > 28) {
    PA_SetSpriteXY(1, SPRITE_NB_WALL1_PART2, 110, 192+28-m_wall);
    if (m_wall > 28+28) {
      PA_SetSpriteXY(1, SPRITE_NB_WALL1_PART3, 110, 192+28+28-m_wall);
      if (m_wall > 28+28+28)
        PA_SetSpriteXY(1, SPRITE_NB_WALL1_PART4, 110, 192+28+28+28-m_wall);
      else
        PA_SetSpriteXY(1, SPRITE_NB_WALL1_PART4, 110+256, 192+28+28+28-m_wall);
    } else {
      PA_SetSpriteXY(1, SPRITE_NB_WALL1_PART3, 110+256, 192+28+28-m_wall);
      PA_SetSpriteXY(1, SPRITE_NB_WALL1_PART4, 110+256, 192+28+28+28-m_wall);
    }
  } else {
    PA_SetSpriteXY(1, SPRITE_NB_WALL1_PART2, 110+256, 192+28-m_wall);
    PA_SetSpriteXY(1, SPRITE_NB_WALL1_PART3, 110+256, 192+28+28-m_wall);
    PA_SetSpriteXY(1, SPRITE_NB_WALL1_PART4, 110+256, 192+28+28+28-m_wall);
  }
}

void CPlayer1::hideCastle(void) { 
  PA_DeleteSprite(1, SPRITE_NB_CASTLE1_PART1);
  PA_DeleteSprite(1, SPRITE_NB_CASTLE1_PART2);
  PA_DeleteSprite(1, SPRITE_NB_WALL1_PART1);
  PA_DeleteSprite(1, SPRITE_NB_WALL1_PART2);
  PA_DeleteSprite(1, SPRITE_NB_WALL1_PART3);
  PA_DeleteSprite(1, SPRITE_NB_WALL1_PART4);
}

void CPlayer1::displayChanges(void) {
  char str[3];
  ostringstream number;
  if (m_defensevc != 0) {
    memset(str, 0, sizeof(str));
    number.str("");
    if (m_defensevc > 0) {
      number << "+" << ABS(m_defensevc);
      strncpy (str, number.str().c_str(), 3);
      PA_16cText(1, 66, 9, 100, 7+7, str, 3, 0, 100);
    }
    else {
      number << "-" << ABS(m_defensevc);
      strncpy (str, number.str().c_str(), 3);
      PA_16cText(1, 66, 9, 100, 7+7, str, 2, 0, 100);
    }
  }
  if (m_attackvc != 0) {
    memset(str, 0, sizeof(str));
    number.str("");
    if (m_attackvc > 0) {
      number << "+" << ABS(m_attackvc);
      strncpy (str, number.str().c_str(), 3);
      PA_16cText(1, 66, 9+48, 100, 7+48+7, str, 3, 0, 100);
    } else {
      number << "-" << ABS(m_attackvc);
      strncpy (str, number.str().c_str(), 3);
      PA_16cText(1, 66, 9+48, 100, 7+48+7, str, 2, 0, 100);
    }
  }
  if (m_magicvc != 0) {
    memset(str, 0, sizeof(str));
    number.str("");
    if (m_magicvc > 0) {
      number << "+" << ABS(m_magicvc);
      strncpy (str, number.str().c_str(), 3);
      PA_16cText(1, 66, 9+48+48, 100, 7+48+48+7, str, 3, 0, 100);
    } else {
      number << "-" << ABS(m_magicvc);
      strncpy (str, number.str().c_str(), 3);
      PA_16cText(1, 66, 9+48+48, 100, 7+48+48+7, str, 2, 0, 100);
    }
  }
  if (m_castlec != 0) {
    memset(str, 0, sizeof(str));
    number.str("");
    if (m_castlec > 0) {
      number << "+" << ABS(m_castlec);
      strncpy (str, number.str().c_str(), 3);
      PA_16cText(1, 66, 9+48+48+48, 100, 7+48+48+48+7, str, 3, 0, 100);
    }
    else {
      number << "-" << ABS(m_castlec);
      strncpy (str, number.str().c_str(), 3);
      PA_16cText(1, 66, 9+48+48+48, 100, 7+48+48+48+7, str, 2, 0, 100);
    }
  }
  if (m_defensec != 0) {
    memset(str, 0, sizeof(str));
    number.str("");
    if (m_defensec > 0) {
      number << "+" << ABS(m_defensec);
      strncpy (str, number.str().c_str(), 3);
      PA_16cText(1, 66, 9+24, 100, 7+24+7, str, 3, 0, 100);
    } else {
      number << "-" << ABS(m_defensec);
      strncpy (str, number.str().c_str(), 3);
      PA_16cText(1, 66, 9+24, 100, 7+24+7, str, 2, 0, 100);
    }
  }
  if (m_attackc != 0) {
    memset(str, 0, sizeof(str));
    number.str("");
    if (m_attackc > 0) {
      number << "+" << ABS(m_attackc);
      strncpy (str, number.str().c_str(), 3);
      PA_16cText(1, 66, 9+24+48, 100, 7+24+48+7, str, 3, 0, 100);
    } else {
      number << "-" << ABS(m_attackc);
      strncpy (str, number.str().c_str(), 3);
      PA_16cText(1, 66, 9+24+48, 100, 7+24+48+7, str, 2, 0, 100);
    }
  }
  if (m_magicc != 0) {
    memset(str, 0, sizeof(str));
    number.str("");
    if (m_magicc > 0) {
      number << "+" << ABS(m_magicc);
      strncpy (str, number.str().c_str(), 3);
      PA_16cText(1, 66, 9+24+48+48, 100, 7+24+48+48+7, str, 3, 0, 100);
    } else {
      number << "-" << ABS(m_magicc);
      strncpy (str, number.str().c_str(), 3);
      PA_16cText(1, 66, 9+24+48+48, 100, 7+24+48+48+7, str, 2, 0, 100);
    }
  }
  if (m_wallc != 0) {
    memset(str, 0, sizeof(str));
    number.str("");
    if (m_wallc > 0) {
      number << "+" << ABS(m_wallc);
      strncpy (str, number.str().c_str(), 3);
      PA_16cText(1, 66, 9+24+48+48+48, 100, 7+24+48+48+48+7, str, 3, 0, 100);
    } else {
      number << "-" << ABS(m_wallc);
      strncpy (str, number.str().c_str(), 3);
      PA_16cText(1, 66, 9+24+48+48+48, 100, 7+24+48+48+48+7, str, 2, 0, 100);
    }
  }
}
