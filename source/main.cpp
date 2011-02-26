#include <PA9.h>
#include <fat.h>
#include "define.h"
#include "CMenu.h"

// Gfx
#include "gfx/castle.pal.c"
#include "gfx/item.pal.c"

int main(int argc, char ** argv) {  
  // General initializations
  PA_Init();
  PA_InitVBL();
  PA_InitRand();
#ifndef DEBUG
  // Sound init to play mp3 and/or sfx
  PA_InitASLibForMP3(AS_MODE_MP3 | AS_MODE_SURROUND | AS_MODE_16CH);
#endif
  // Initialize the Wifi handler
  l_wifi.initialize();
#ifndef DEBUG
  // Set the sound settings
  AS_SetDefaultSettings(AS_PCM_8BIT, 44100, AS_SURROUND);
#endif
  // Initialize the background transitions
  PA_InitBgTrans(0);
  PA_BgTransDiag(0, TRANSITION_TYPE, 0, 1, 0);
  // Load sprite palettes
  PA_LoadSpritePal(1, PALETTE_NB_CASTLE, (void*)castle_Pal);
  PA_LoadSpritePal(1, PALETTE_NB_ITEM, (void*)item_Pal);
  // Enable alpha blending at the bottom and top screens
  PA_EnableSpecialFx(0, SFX_ALPHA, 0, SFX_BG0 | SFX_BG1 | SFX_BG2 | SFX_BG3 | SFX_BD);
  PA_SetSFXAlpha(0,	7, 15);
  PA_EnableSpecialFx(1, SFX_ALPHA, 0, SFX_BG0 | SFX_BG1 | SFX_BG2 | SFX_BG3 | SFX_BD);
  PA_SetSFXAlpha(1,	7, 15);
  // Main menu object
  CMenu l_menu;
  while(1) {
    // Display the menu
    l_menu.displayMenu();
  }
  return 0;
}
