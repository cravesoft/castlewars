#include "CMenu.h"

// Gfx
#include "gfx/bottomscreen.pal.c"
#include "gfx/bottomscreen.c"
#include "gfx/menu2.pal.c"
#include "gfx/menu2.c"
#include "gfx/grass.pal.c"
#include "gfx/grass.c"
#include "gfx/title.pal.c"
#include "gfx/title.c"
#include "gfx/topcastle.c"
#include "gfx/castle.c"
#include "gfx/hotseat_wifi.pal.c"
#include "gfx/hotseat_wifi.c"
#include "gfx/instructions1.pal.c"
#include "gfx/instructions1.c"
#include "gfx/instructions2.pal.c"
#include "gfx/instructions2.c"
#include "gfx/instructions3.pal.c"
#include "gfx/instructions3.c"
#include "gfx/defense9_1.c"
#include "gfx/defense9_2.c"
#include "gfx/defense9.pal.c"
#include "gfx/opponentchoice.pal.c"
#include "gfx/opponentchoice.c"

// Music
#include "sound9.h"

CMenu::CMenu(void) : m_itemTouched(NO_MODE) {
  m_musicVolume = MUSIC_VOLUME;
  m_cardSpeed = CARD_SPEED;
}

CMenu::~CMenu(void) {}

void CMenu::displayInstructions() {
  // Display the first instructions screen
  PA_DeleteBg (0, 0);
  PA_EasyBgLoad(0, 0, instructions1);
  PA_WaitForVBL();
  while(!Stylus.Released)
    PA_WaitForVBL();
  // Display the second instructions screen
  PA_DeleteBg (0, 0);
  PA_EasyBgLoad(0, 0, instructions2);
  PA_WaitForVBL();
  while(!Stylus.Released)
    PA_WaitForVBL();
  PA_DeleteBg (0, 0);
  // Display the third instructions screen
  PA_EasyBgLoad(0, 0, instructions3);
  // Display the sprites of the example card at the center of the bottom screen
  PA_DualLoadSpritePal(PALETTE_NB_CARD, (void*)defense9_Pal);
  PA_DualCreateSprite(SPRITE_NB_BACKCARD_PART1, (void*)defense9_1_Sprite,
                      OBJ_SIZE_64X64, 1, PALETTE_NB_CARD, 97, 42+48+192);
  PA_DualCreateSprite(SPRITE_NB_BACKCARD_PART2, (void*)defense9_2_Sprite,
                      OBJ_SIZE_64X64, 1, PALETTE_NB_CARD, 97, 42+45+48+192);
  PA_WaitForVBL();
  while(!Stylus.Released)
    PA_WaitForVBL();
  // Delete the sprites of the example card
  PA_DualDeleteSprite(SPRITE_NB_BACKCARD_PART1);
  PA_DualDeleteSprite(SPRITE_NB_BACKCARD_PART2);
  // Replace the third instruction screen with the main menu 
  PA_DeleteBg (0, 0);
  PA_EasyBgLoad(0, 0, menu2);
  m_itemTouched = NO_MODE;
  PA_WaitForVBL();
}

u16 CMenu::itemTouched() {
  u16 posX, posY;
  if (Stylus.Released) {
    posX = Stylus.X;
    posY = Stylus.Y;
    if (m_itemTouched == MODE_TWOPLAYERS) {  // Main menu
      if ((posX > 95) && (posX < 159) && (posY > 37) && (posY < 56))
        return MODE_HOTSEAT;
      if ((posX > 102) && (posX < 149) && (posY > 84) && (posY < 105))
        return MODE_WIFI;
      if ((posX > 104) && (posX < 149) && (posY > 132) && (posY < 152))
        return BACK;
      return MODE_TWOPLAYERS;
    } else {  // Two players menu
      if ((posX > 38) && (posX < 217) && (posY > 12) && (posY < 37))
        return MODE_ONEPLAYER;
      if ((posX > 48) && (posX < 224) && (posY > 61) && (posY < 86))
        return MODE_TWOPLAYERS;
      if ((posX > 28) && (posX < 226) && (posY > 108) && (posY < 133))
        return MODE_TWOCOMPS;
      if ((posX > 80) && (posX < 171) && (posY > 156) && (posY < 177))
        return MODE_INSTRUCTIONS;
      return m_itemTouched;
    }
  }
  else
    return m_itemTouched;
}

void CMenu::displayMenu(void) {
  u16 position_castle(36);
  s8 l_i;
  // Reset the background system
  PA_ResetBgSys();
  // Initialize the text at the top and bottom screens
  PA_InitText(1,0);
  PA_Init16cBg(1, 1);
  //PA_Init16cBg(1, 1);
  //PA_InitCustomText(1, 0, PA_Text);
  //PA_InitText(0,0);
  PA_Init16cBg(0, 1);
  // Load the grass background at the top screen
  PA_EasyBgLoad(1, 2, grass);
  // Set the screens' brightness to white 
  PA_SetBrightness(1, 31);
  PA_SetBrightness(0, 31);
  // Load the title background at the top screen 
  PA_EasyBgLoad(1, 3, title);
  // Change the brightness of the top screen to neutral (fading)
  for (l_i = 31; l_i >= 0; l_i--) {
  	PA_SetBrightness(1, l_i);
  	PA_WaitForVBL();
  	PA_WaitForVBL();
  }
  // Create the sprites for the two castles below the grass level
  PA_DualCreateSprite(SPRITE_NB_CASTLE1_PART1, (void*)topcastle_Sprite,
                      OBJ_SIZE_64X64, 1, PALETTE_NB_CASTLE,
                      69, 192-position_castle);
  PA_DualCreateSprite(SPRITE_NB_CASTLE1_PART2, (void*)castle_Sprite,
                      OBJ_SIZE_64X64, 1, PALETTE_NB_CASTLE,
                      69, 192+64-position_castle);
  PA_DualCreateSprite(SPRITE_NB_CASTLE2_PART1, (void*)topcastle_Sprite,
                      OBJ_SIZE_64X64, 1, PALETTE_NB_CASTLE,
                      151, 192-position_castle);
  PA_DualCreateSprite(SPRITE_NB_CASTLE2_PART2, (void*)castle_Sprite,
                      OBJ_SIZE_64X64, 1, PALETTE_NB_CASTLE,
                      151, 192+64-position_castle);
  // Display the castle sprites behind the grass
  PA_DualSetSpritePrio (SPRITE_NB_CASTLE1_PART1, 3);
  PA_DualSetSpritePrio (SPRITE_NB_CASTLE1_PART2, 3);
  PA_DualSetSpritePrio (SPRITE_NB_CASTLE2_PART1, 3);
  PA_DualSetSpritePrio (SPRITE_NB_CASTLE2_PART2, 3);
  // Move gradually the castle sprites above the grass
  for (position_castle = 36; position_castle <= 90; position_castle++) {
    PA_WaitForVBL();
    PA_DualSetSpriteXY(SPRITE_NB_CASTLE1_PART1, 69, 192-position_castle);
    PA_DualSetSpriteXY(SPRITE_NB_CASTLE1_PART2, 69, 192+64-position_castle);
    PA_DualSetSpriteXY(SPRITE_NB_CASTLE2_PART1, 151, 192-position_castle);
    PA_DualSetSpriteXY(SPRITE_NB_CASTLE2_PART2, 151, 192+64-position_castle);
  }
  // Display the main menu
  PA_EasyBgLoad(0, 0, menu2);
  PA_SetBrightness(0, 0);
  // Wait for a player's action
  m_itemTouched = NO_MODE;
  while ((m_itemTouched == NO_MODE) || (m_itemTouched == MODE_TWOPLAYERS) || (m_itemTouched == BACK)) {
    m_itemTouched = itemTouched();
    if (m_itemTouched == MODE_INSTRUCTIONS)
      displayInstructions();
    if (m_itemTouched == MODE_TWOPLAYERS) {
      PA_DeleteBg (0, 0);
      PA_EasyBgLoad(0, 0, hotseat_wifi);
    }
    if (m_itemTouched == BACK) {
      PA_DeleteBg (0, 0);
      PA_EasyBgLoad(0, 0, menu2);
    }
    PA_WaitForVBL();
  }
  // Delete the castle sprites
  PA_DualDeleteSprite(SPRITE_NB_CASTLE1_PART1);
  PA_DualDeleteSprite(SPRITE_NB_CASTLE1_PART2);
  PA_DualDeleteSprite(SPRITE_NB_CASTLE2_PART1);
  PA_DualDeleteSprite(SPRITE_NB_CASTLE2_PART2);
  // Load the empty bottom screen
  PA_EasyBgLoad(0, 3, bottomscreen);
  // Activate the Wifi
  if (m_itemTouched == MODE_WIFI) {
    PA_DeleteBg (0, 0);
    PA_EasyBgLoad(1, 2, opponentchoice);
    l_wifi.goToState(WIFI_STATE_ACTIVE);
    m_playerOrder = l_wifi.connection();
  }
  // Fading to white at the top screen
  for (l_i = 0; l_i <=31; l_i++) {
  	PA_SetBrightness(1, l_i);
  	PA_WaitForVBL();
  	PA_WaitForVBL();
  }
  // Start to play the music
#ifndef DEBUG
  AS_SetMP3Loop(true);
  AS_SetMP3Volume(m_musicVolume);
  AS_MP3DirectPlay((u8*)sound9, (u32)sound9_size);
#endif
  CGame l_game;  // Main game object
  // Initialise the game object where m_itemTouched corresponds to the game mode
  l_game.initGame(m_musicVolume, m_cardSpeed, m_itemTouched, m_playerOrder);
  // Infinite loop to keep the program running
  bool finish = false;
  while(!finish) {
    // Play the game
    finish = l_game.play(&m_musicVolume, &m_cardSpeed);
    PA_WaitForVBL();
  }
  // Stop the music
#ifndef DEBUG
  AS_MP3Stop();
#endif
}
