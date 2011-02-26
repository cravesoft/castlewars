#include "CDeck.h"

// Gfx
#include "gfx/backcard.c"
#include "gfx/emptycard.c"
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

CDeck::CDeck(void) {
  PA_LoadSpritePal(1, PALETTE_NB_CARD, (void*)card_Pal);
  
  PA_CreateSprite(1, SPRITE_NB_BACKCARD_PART1, (void*)backcard_Sprite,
                  OBJ_SIZE_64X64, 1, PALETTE_NB_CARD, 67, 1);
  PA_CloneSprite(1, SPRITE_NB_BACKCARD_PART2, SPRITE_NB_BACKCARD_PART1);
  PA_SetSpriteVflip(1, SPRITE_NB_BACKCARD_PART2, 1);
  PA_SetSpriteXY(1, SPRITE_NB_BACKCARD_PART2, 67, 1+26);
  
  PA_CreateSprite(1, SPRITE_NB_EMPTYCARD_PART1, (void*)emptycard_Sprite,
                  OBJ_SIZE_64X64, 1, PALETTE_NB_CARD, 129, 1);
  PA_CloneSprite(1, SPRITE_NB_EMPTYCARD_PART2, SPRITE_NB_EMPTYCARD_PART1);
  PA_SetSpriteVflip(1, SPRITE_NB_EMPTYCARD_PART2, 1);
  PA_SetSpriteXY(1, SPRITE_NB_EMPTYCARD_PART2, 129, 1+26);
  
  PA_SetSpritePrio (1, SPRITE_NB_BACKCARD_PART1, 2);
  PA_SetSpritePrio (1, SPRITE_NB_BACKCARD_PART2, 2);
  PA_SetSpritePrio (1, SPRITE_NB_EMPTYCARD_PART1, 2);
  PA_SetSpritePrio (1, SPRITE_NB_EMPTYCARD_PART2, 2);
}

CDeck::~CDeck(void) {
  PA_DeleteSprite(1, SPRITE_NB_BACKCARD_PART1);
  PA_DeleteSprite(1, SPRITE_NB_BACKCARD_PART2);
  PA_DeleteSprite(1, SPRITE_NB_EMPTYCARD_PART1);
  PA_DeleteSprite(1, SPRITE_NB_EMPTYCARD_PART2);
}

void CDeck::reset(void) {
  // reset the card frequencies
  for (u8 i = 0; i < 3; i++) {
    for (u8 j = 0; j < 6; j++)
      m_cardfrequency[typecard(i, j)] = 3; // 3 cards for the lowest values
    for (u8 j = 6; j < 10; j++)
      m_cardfrequency[typecard(i, j)] = 2; // 2 cards for the highest values
  }
}

void CDeck::display(void) {}

void CDeck::pickCard(typecard* p_card, int p_playerID) {
  // Randomly pick a card in the deck
  p_card->first =  PA_RandMax(2);
  p_card->second = PA_RandMax(9);
  while (m_cardfrequency[*p_card] <= 0) {
    p_card->first  = PA_RandMax(2);
    p_card->second = PA_RandMax(9);
  }
  if (p_playerID == HUMAN_GET) {  // Receive the information
    p_card->first  = l_wifi.getIntInfo();
    p_card->second = l_wifi.getIntInfo();
  }
  if (p_playerID == HUMAN_SEND) {  // Send the information
    l_wifi.sendIntInfo(p_card->first);
    l_wifi.sendIntInfo(p_card->second);
  }
  m_cardfrequency[*p_card]--;
}

void CDeck::hideDeck(void) {
  PA_DeleteSprite(1, SPRITE_NB_BACKCARD_PART1);
  PA_DeleteSprite(1, SPRITE_NB_BACKCARD_PART2);
  PA_DeleteSprite(1, SPRITE_NB_EMPTYCARD_PART1);
  PA_DeleteSprite(1, SPRITE_NB_EMPTYCARD_PART2);
}

void CDeck::discardCard(const typecard card, const bool discarded) {
  m_cardfrequency[card]++;
  // Delete the previously played card sprite at the top screen
  PA_DeleteSprite(1, SPRITE_NB_EMPTYCARD_PART2);
  PA_DeleteSprite(1, SPRITE_NB_EMPTYCARD_PART1);
  // Create a sprite for the card that has been discarded at the top screen
  switch (card.first) {
    case 0:
      switch (card.second) {
        case 0:
          PA_LoadSpritePal(1, PALETTE_NB_LAST_PLAYED_CARD, (void*)attack1_Pal);
          PA_CreateSprite(1, SPRITE_NB_EMPTYCARD_PART1, (void*)attack1_1_Sprite,
                             OBJ_SIZE_64X64, 1, PALETTE_NB_LAST_PLAYED_CARD,
                             129, 1);
          PA_CreateSprite(1, SPRITE_NB_EMPTYCARD_PART2, (void*)attack1_2_Sprite,
                          OBJ_SIZE_64X64, 1, PALETTE_NB_LAST_PLAYED_CARD,
                          129, 1+45);
          break;
        case 1:
          PA_LoadSpritePal(1, PALETTE_NB_LAST_PLAYED_CARD, (void*)attack2_Pal);
          PA_CreateSprite(1, SPRITE_NB_EMPTYCARD_PART1, (void*)attack2_1_Sprite,
                          OBJ_SIZE_64X64, 1, PALETTE_NB_LAST_PLAYED_CARD,
                          129, 1);
          PA_CreateSprite(1, SPRITE_NB_EMPTYCARD_PART2, (void*)attack2_2_Sprite,
                          OBJ_SIZE_64X64, 1, PALETTE_NB_LAST_PLAYED_CARD,
                          129, 1+45);
          break;
        case 2:
          PA_LoadSpritePal(1, PALETTE_NB_LAST_PLAYED_CARD, (void*)attack3_Pal);
          PA_CreateSprite(1, SPRITE_NB_EMPTYCARD_PART1, (void*)attack3_1_Sprite,
                          OBJ_SIZE_64X64, 1, PALETTE_NB_LAST_PLAYED_CARD,
                          129, 1);
          PA_CreateSprite(1, SPRITE_NB_EMPTYCARD_PART2, (void*)attack3_2_Sprite,
                          OBJ_SIZE_64X64, 1, PALETTE_NB_LAST_PLAYED_CARD,
                          129, 1+45);
          break;
        case 3:
          PA_LoadSpritePal(1, PALETTE_NB_LAST_PLAYED_CARD, (void*)attack4_Pal);
          PA_CreateSprite(1, SPRITE_NB_EMPTYCARD_PART1, (void*)attack4_1_Sprite,
                          OBJ_SIZE_64X64, 1, PALETTE_NB_LAST_PLAYED_CARD,
                          129, 1);
          PA_CreateSprite(1, SPRITE_NB_EMPTYCARD_PART2, (void*)attack4_2_Sprite,
                          OBJ_SIZE_64X64, 1, PALETTE_NB_LAST_PLAYED_CARD,
                          129, 1+45);
          break;
        case 4:
          PA_LoadSpritePal(1, PALETTE_NB_LAST_PLAYED_CARD, (void*)attack5_Pal);
          PA_CreateSprite(1, SPRITE_NB_EMPTYCARD_PART1, (void*)attack5_1_Sprite,
                          OBJ_SIZE_64X64, 1, PALETTE_NB_LAST_PLAYED_CARD,
                          129, 1);
          PA_CreateSprite(1, SPRITE_NB_EMPTYCARD_PART2, (void*)attack5_2_Sprite,
                          OBJ_SIZE_64X64, 1, PALETTE_NB_LAST_PLAYED_CARD,
                          129, 1+45);
          break;
        case 5:
          PA_LoadSpritePal(1, PALETTE_NB_LAST_PLAYED_CARD, (void*)attack6_Pal);
          PA_CreateSprite(1, SPRITE_NB_EMPTYCARD_PART1, (void*)attack6_1_Sprite,
                          OBJ_SIZE_64X64, 1, PALETTE_NB_LAST_PLAYED_CARD,
                          129, 1);
          PA_CreateSprite(1, SPRITE_NB_EMPTYCARD_PART2, (void*)attack6_2_Sprite,
                          OBJ_SIZE_64X64, 1, PALETTE_NB_LAST_PLAYED_CARD, 
                          129, 1+45);
          break;
        case 6:
          PA_LoadSpritePal(1, PALETTE_NB_LAST_PLAYED_CARD, (void*)attack7_Pal);
          PA_CreateSprite(1, SPRITE_NB_EMPTYCARD_PART1, (void*)attack7_1_Sprite,
                          OBJ_SIZE_64X64, 1, PALETTE_NB_LAST_PLAYED_CARD,
                          129, 1);
          PA_CreateSprite(1, SPRITE_NB_EMPTYCARD_PART2, (void*)attack7_2_Sprite,
                          OBJ_SIZE_64X64, 1, PALETTE_NB_LAST_PLAYED_CARD,
                          129, 1+45);
          break;
        case 7:
          PA_LoadSpritePal(1, PALETTE_NB_LAST_PLAYED_CARD, (void*)attack8_Pal);
          PA_CreateSprite(1, SPRITE_NB_EMPTYCARD_PART1, (void*)attack8_1_Sprite,
                          OBJ_SIZE_64X64, 1, PALETTE_NB_LAST_PLAYED_CARD,
                          129, 1);
          PA_CreateSprite(1, SPRITE_NB_EMPTYCARD_PART2, (void*)attack8_2_Sprite,
                          OBJ_SIZE_64X64, 1, PALETTE_NB_LAST_PLAYED_CARD,
                          129, 1+45);
          break;
        case 8:
          PA_LoadSpritePal(1, PALETTE_NB_LAST_PLAYED_CARD, (void*)attack9_Pal);
          PA_CreateSprite(1, SPRITE_NB_EMPTYCARD_PART1, (void*)attack9_1_Sprite,
                          OBJ_SIZE_64X64, 1, PALETTE_NB_LAST_PLAYED_CARD,
                          129, 1);
          PA_CreateSprite(1, SPRITE_NB_EMPTYCARD_PART2, (void*)attack9_2_Sprite,
                          OBJ_SIZE_64X64, 1, PALETTE_NB_LAST_PLAYED_CARD,
                          129, 1+45);
          break;
        case 9:
          PA_LoadSpritePal(1, PALETTE_NB_LAST_PLAYED_CARD, (void*)attack10_Pal);
          PA_CreateSprite(1, SPRITE_NB_EMPTYCARD_PART1,
                          (void*)attack10_1_Sprite, OBJ_SIZE_64X64, 1,
                          PALETTE_NB_LAST_PLAYED_CARD, 129, 1);
          PA_CreateSprite(1, SPRITE_NB_EMPTYCARD_PART2,
                          (void*)attack10_2_Sprite, OBJ_SIZE_64X64, 1,
                          PALETTE_NB_LAST_PLAYED_CARD, 129, 1+45);
          break;
        default:
          PA_OutputText(1,0,0,"This card number does not exist.");
          break;
      }
      break;
    case 1:
      switch (card.second) {
        case 0:
          PA_LoadSpritePal(1, PALETTE_NB_LAST_PLAYED_CARD, (void*)defense1_Pal);
          PA_CreateSprite(1, SPRITE_NB_EMPTYCARD_PART1,
                          (void*)defense1_1_Sprite, OBJ_SIZE_64X64, 1,
                          PALETTE_NB_LAST_PLAYED_CARD, 129, 1);
          PA_CreateSprite(1, SPRITE_NB_EMPTYCARD_PART2,
                          (void*)defense1_2_Sprite, OBJ_SIZE_64X64, 1,
                          PALETTE_NB_LAST_PLAYED_CARD, 129, 1+45);
          break;
        case 1:
          PA_LoadSpritePal(1, PALETTE_NB_LAST_PLAYED_CARD, (void*)defense2_Pal);
          PA_CreateSprite(1, SPRITE_NB_EMPTYCARD_PART1,
                          (void*)defense2_1_Sprite, OBJ_SIZE_64X64, 1,
                          PALETTE_NB_LAST_PLAYED_CARD, 129, 1);
          PA_CreateSprite(1, SPRITE_NB_EMPTYCARD_PART2,
                          (void*)defense2_2_Sprite, OBJ_SIZE_64X64, 1,
                          PALETTE_NB_LAST_PLAYED_CARD, 129, 1+45);
          break;
        case 2:
          PA_LoadSpritePal(1, PALETTE_NB_LAST_PLAYED_CARD, (void*)defense3_Pal);
          PA_CreateSprite(1, SPRITE_NB_EMPTYCARD_PART1,
                          (void*)defense3_1_Sprite, OBJ_SIZE_64X64, 1,
                          PALETTE_NB_LAST_PLAYED_CARD, 129, 1);
          PA_CreateSprite(1, SPRITE_NB_EMPTYCARD_PART2,
                          (void*)defense3_2_Sprite, OBJ_SIZE_64X64, 1,
                          PALETTE_NB_LAST_PLAYED_CARD, 129, 1+45);
          break;
        case 3:
          PA_LoadSpritePal(1, PALETTE_NB_LAST_PLAYED_CARD, (void*)defense4_Pal);
          PA_CreateSprite(1, SPRITE_NB_EMPTYCARD_PART1,
                          (void*)defense4_1_Sprite, OBJ_SIZE_64X64, 1,
                          PALETTE_NB_LAST_PLAYED_CARD, 129, 1);
          PA_CreateSprite(1, SPRITE_NB_EMPTYCARD_PART2,
                          (void*)defense4_2_Sprite, OBJ_SIZE_64X64, 1,
                          PALETTE_NB_LAST_PLAYED_CARD, 129, 1+45);
          break;
        case 4:
          PA_LoadSpritePal(1, PALETTE_NB_LAST_PLAYED_CARD, (void*)defense5_Pal);
          PA_CreateSprite(1, SPRITE_NB_EMPTYCARD_PART1,
                          (void*)defense5_1_Sprite, OBJ_SIZE_64X64, 1,
                          PALETTE_NB_LAST_PLAYED_CARD, 129, 1);
          PA_CreateSprite(1, SPRITE_NB_EMPTYCARD_PART2,
                          (void*)defense5_2_Sprite, OBJ_SIZE_64X64, 1,
                          PALETTE_NB_LAST_PLAYED_CARD, 129, 1+45);
          break;
        case 5:
          PA_LoadSpritePal(1, PALETTE_NB_LAST_PLAYED_CARD, (void*)defense6_Pal);
          PA_CreateSprite(1, SPRITE_NB_EMPTYCARD_PART1,
                          (void*)defense6_1_Sprite, OBJ_SIZE_64X64, 1,
                          PALETTE_NB_LAST_PLAYED_CARD, 129, 1);
          PA_CreateSprite(1, SPRITE_NB_EMPTYCARD_PART2,
                          (void*)defense6_2_Sprite, OBJ_SIZE_64X64, 1,
                          PALETTE_NB_LAST_PLAYED_CARD, 129, 1+45);
          break;
        case 6:
          PA_LoadSpritePal(1, PALETTE_NB_LAST_PLAYED_CARD, (void*)defense7_Pal);
          PA_CreateSprite(1, SPRITE_NB_EMPTYCARD_PART1,
                          (void*)defense7_1_Sprite, OBJ_SIZE_64X64, 1,
                          PALETTE_NB_LAST_PLAYED_CARD, 129, 1);
          PA_CreateSprite(1, SPRITE_NB_EMPTYCARD_PART2,
                          (void*)defense7_2_Sprite, OBJ_SIZE_64X64, 1,
                          PALETTE_NB_LAST_PLAYED_CARD, 129, 1+45);
          break;
        case 7:
          PA_LoadSpritePal(1, PALETTE_NB_LAST_PLAYED_CARD, (void*)defense8_Pal);
          PA_CreateSprite(1, SPRITE_NB_EMPTYCARD_PART1,
                          (void*)defense8_1_Sprite, OBJ_SIZE_64X64, 1,
                          PALETTE_NB_LAST_PLAYED_CARD, 129, 1);
          PA_CreateSprite(1, SPRITE_NB_EMPTYCARD_PART2,
                          (void*)defense8_2_Sprite, OBJ_SIZE_64X64, 1,
                          PALETTE_NB_LAST_PLAYED_CARD, 129, 1+45);
          break;
        case 8:
          PA_LoadSpritePal(1, PALETTE_NB_LAST_PLAYED_CARD, (void*)defense9_Pal);
          PA_CreateSprite(1, SPRITE_NB_EMPTYCARD_PART1,
                          (void*)defense9_1_Sprite, OBJ_SIZE_64X64, 1,
                          PALETTE_NB_LAST_PLAYED_CARD, 129, 1);
          PA_CreateSprite(1, SPRITE_NB_EMPTYCARD_PART2,
                          (void*)defense9_2_Sprite, OBJ_SIZE_64X64, 1,
                          PALETTE_NB_LAST_PLAYED_CARD, 129, 1+45);
          break;
        case 9:
          PA_LoadSpritePal(1, PALETTE_NB_LAST_PLAYED_CARD,
                           (void*)defense10_Pal);
          PA_CreateSprite(1, SPRITE_NB_EMPTYCARD_PART1,
                          (void*)defense10_1_Sprite, OBJ_SIZE_64X64, 1,
                          PALETTE_NB_LAST_PLAYED_CARD, 129, 1);
          PA_CreateSprite(1, SPRITE_NB_EMPTYCARD_PART2,
                          (void*)defense10_2_Sprite, OBJ_SIZE_64X64, 1,
                          PALETTE_NB_LAST_PLAYED_CARD, 129, 1+45);
          break;
        default:
          PA_OutputText(1,0,0,"This card number does not exist.");
          break;
      }
      break;
    case 2:
      switch (card.second) {
        case 0:
          PA_LoadSpritePal(1, PALETTE_NB_LAST_PLAYED_CARD, (void*)magic1_Pal);
          PA_CreateSprite(1, SPRITE_NB_EMPTYCARD_PART1, (void*)magic1_1_Sprite,
                          OBJ_SIZE_64X64, 1, PALETTE_NB_LAST_PLAYED_CARD,
                          129, 1);
          PA_CreateSprite(1, SPRITE_NB_EMPTYCARD_PART2, (void*)magic1_2_Sprite,
                          OBJ_SIZE_64X64, 1, PALETTE_NB_LAST_PLAYED_CARD,
                          129, 1+45);
          break;
        case 1:
          PA_LoadSpritePal(1, PALETTE_NB_LAST_PLAYED_CARD, (void*)magic2_Pal);
          PA_CreateSprite(1, SPRITE_NB_EMPTYCARD_PART1, (void*)magic2_1_Sprite,
                          OBJ_SIZE_64X64, 1, PALETTE_NB_LAST_PLAYED_CARD,
                          129, 1);
          PA_CreateSprite(1, SPRITE_NB_EMPTYCARD_PART2, (void*)magic2_2_Sprite,
                          OBJ_SIZE_64X64, 1, PALETTE_NB_LAST_PLAYED_CARD, 129,
                          1+45);
          break;
        case 2:
          PA_LoadSpritePal(1, PALETTE_NB_LAST_PLAYED_CARD, (void*)magic3_Pal);
          PA_CreateSprite(1, SPRITE_NB_EMPTYCARD_PART1, (void*)magic3_1_Sprite,
                          OBJ_SIZE_64X64, 1, PALETTE_NB_LAST_PLAYED_CARD,
                          129, 1);
          PA_CreateSprite(1, SPRITE_NB_EMPTYCARD_PART2, (void*)magic3_2_Sprite,
                          OBJ_SIZE_64X64, 1, PALETTE_NB_LAST_PLAYED_CARD,
                          129, 1+45);
          break;
        case 3:
          PA_LoadSpritePal(1, PALETTE_NB_LAST_PLAYED_CARD, (void*)magic4_Pal);
          PA_CreateSprite(1, SPRITE_NB_EMPTYCARD_PART1, (void*)magic4_1_Sprite,
                          OBJ_SIZE_64X64, 1, PALETTE_NB_LAST_PLAYED_CARD,
                          129, 1);
          PA_CreateSprite(1, SPRITE_NB_EMPTYCARD_PART2, (void*)magic4_2_Sprite,
                          OBJ_SIZE_64X64, 1, PALETTE_NB_LAST_PLAYED_CARD,
                          129, 1+45);
          break;
        case 4:
          PA_LoadSpritePal(1, PALETTE_NB_LAST_PLAYED_CARD, (void*)magic5_Pal);
          PA_CreateSprite(1, SPRITE_NB_EMPTYCARD_PART1, (void*)magic5_1_Sprite,
                            OBJ_SIZE_64X64, 1, PALETTE_NB_LAST_PLAYED_CARD,
                            129, 1);
          PA_CreateSprite(1, SPRITE_NB_EMPTYCARD_PART2, (void*)magic5_2_Sprite,
                          OBJ_SIZE_64X64, 1, PALETTE_NB_LAST_PLAYED_CARD,
                          129, 1+45);
          break;
        case 5:
          PA_LoadSpritePal(1, PALETTE_NB_LAST_PLAYED_CARD, (void*)magic6_Pal);
          PA_CreateSprite(1, SPRITE_NB_EMPTYCARD_PART1, (void*)magic6_1_Sprite,
                          OBJ_SIZE_64X64, 1, PALETTE_NB_LAST_PLAYED_CARD,
                          129, 1);
          PA_CreateSprite(1, SPRITE_NB_EMPTYCARD_PART2, (void*)magic6_2_Sprite,
                          OBJ_SIZE_64X64, 1, PALETTE_NB_LAST_PLAYED_CARD,
                          129, 1+45);
          break;
        case 6:
          PA_LoadSpritePal(1, PALETTE_NB_LAST_PLAYED_CARD, (void*)magic7_Pal);
          PA_CreateSprite(1, SPRITE_NB_EMPTYCARD_PART1, (void*)magic7_1_Sprite,
                          OBJ_SIZE_64X64, 1, PALETTE_NB_LAST_PLAYED_CARD,
                          129, 1);
          PA_CreateSprite(1, SPRITE_NB_EMPTYCARD_PART2, (void*)magic7_2_Sprite,
                          OBJ_SIZE_64X64, 1, PALETTE_NB_LAST_PLAYED_CARD,
                          129, 1+45);
          break;
        case 7:
          PA_LoadSpritePal(1, PALETTE_NB_LAST_PLAYED_CARD, (void*)magic8_Pal);
          PA_CreateSprite(1, SPRITE_NB_EMPTYCARD_PART1, (void*)magic8_1_Sprite,
                          OBJ_SIZE_64X64, 1, PALETTE_NB_LAST_PLAYED_CARD,
                          129, 1);
          PA_CreateSprite(1, SPRITE_NB_EMPTYCARD_PART2, (void*)magic8_2_Sprite,
                          OBJ_SIZE_64X64, 1, PALETTE_NB_LAST_PLAYED_CARD,
                          129, 1+45);
          break;
        case 8:
          PA_LoadSpritePal(1, PALETTE_NB_LAST_PLAYED_CARD, (void*)magic9_Pal);
          PA_CreateSprite(1, SPRITE_NB_EMPTYCARD_PART1, (void*)magic9_1_Sprite,
                          OBJ_SIZE_64X64, 1, PALETTE_NB_LAST_PLAYED_CARD,
                          129, 1);
          PA_CreateSprite(1, SPRITE_NB_EMPTYCARD_PART2, (void*)magic9_2_Sprite,
                          OBJ_SIZE_64X64, 1, PALETTE_NB_LAST_PLAYED_CARD,
                          129, 1+45);
          break;
        case 9:
          PA_LoadSpritePal(1, PALETTE_NB_LAST_PLAYED_CARD, (void*)magic10_Pal);
          PA_CreateSprite(1, SPRITE_NB_EMPTYCARD_PART1, (void*)magic10_1_Sprite,
                          OBJ_SIZE_64X64, 1, PALETTE_NB_LAST_PLAYED_CARD,
                          129, 1);
          PA_CreateSprite(1, SPRITE_NB_EMPTYCARD_PART2, (void*)magic10_2_Sprite,
                          OBJ_SIZE_64X64, 1, PALETTE_NB_LAST_PLAYED_CARD,
                          129, 1+45);
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
  PA_SetSpritePrio (1, SPRITE_NB_BACKCARD_PART1, 2);
  PA_SetSpritePrio (1, SPRITE_NB_BACKCARD_PART2, 2);
  PA_SetSpritePrio (1, SPRITE_NB_EMPTYCARD_PART1, 2);
  PA_SetSpritePrio (1, SPRITE_NB_EMPTYCARD_PART2, 2);
  // Set the sprite's mode to alpha blending if the card is discarded
  if (discarded) {
    PA_SetSpriteMode(1, SPRITE_NB_EMPTYCARD_PART1, 1);
    PA_SetSpriteMode(1, SPRITE_NB_EMPTYCARD_PART2, 1);
  }
  else {
    PA_SetSpriteMode(1, SPRITE_NB_EMPTYCARD_PART1, 0);
    PA_SetSpriteMode(1, SPRITE_NB_EMPTYCARD_PART2, 0);
  }
}
