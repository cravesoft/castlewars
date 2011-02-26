#ifndef DEFINE_H_
#define DEFINE_H_

#include <utility>
#include <math.h>
#include "CWifiHandler.h"
using namespace std;

//#define DEBUG

#define ABS(a)  (((a) < 0) ? -(a) : (a))

#define PAD_NEWPRESS_RIGHT (Pad.Newpress.Right||Pad.Newpress.A)
#define PAD_HELD_RIGHT (Pad.Held.Right||Pad.Held.A)
#define PAD_NEWPRESS_LEFT (Pad.Newpress.Left||Pad.Newpress.Y)
#define PAD_HELD_LEFT (Pad.Held.Left||Pad.Held.Y)
#define PAD_NEWPRESS_DOWN (Pad.Newpress.Down||Pad.Newpress.B)
#define PAD_HELD_DOWN (Pad.Held.Down||Pad.Held.B)

#define TRANSITION_TYPE 0
#define MUSIC_VOLUME 60;
#define CARD_SPEED 10;

#define HUMAN 0
#define COMPUTER 1
#define HUMAN_SEND 2
#define HUMAN_GET 3

#define NO_MODE 0
#define MODE_ONEPLAYER 1
#define MODE_TWOPLAYERS 2
#define MODE_TWOCOMPS 3
#define MODE_INSTRUCTIONS 4
#define MODE_HOTSEAT 5
#define MODE_WIFI 6
#define BACK 7

#define PALETTE_NB_CASTLE 0
#define PALETTE_NB_CARD 1
#define PALETTE_NB_LAST_PLAYED_CARD 2
#define PALETTE_NB_ITEM 3
#define INDEX_PALETTE_NB_CARD 4

#define SPRITE_NB_CASTLE1_PART1 0
#define SPRITE_NB_CASTLE1_PART2 1
#define SPRITE_NB_WALL1_PART1 2
#define SPRITE_NB_WALL1_PART2 3
#define SPRITE_NB_WALL1_PART3 4
#define SPRITE_NB_WALL1_PART4 5
#define SPRITE_NB_CASTLE2_PART1 6
#define SPRITE_NB_CASTLE2_PART2 7
#define SPRITE_NB_WALL2_PART1 8
#define SPRITE_NB_WALL2_PART2 9
#define SPRITE_NB_WALL2_PART3 10
#define SPRITE_NB_WALL2_PART4 11
#define SPRITE_NB_BACKCARD_PART1 12
#define SPRITE_NB_BACKCARD_PART2 13
#define SPRITE_NB_EMPTYCARD_PART1 14
#define SPRITE_NB_EMPTYCARD_PART2 15
#define INDEX_SPRITE_NB_CARD 16
#define INDEX_SPRITE_NB_ITEM_MUSIC 16
#define INDEX_SPRITE_NB_ITEM_SPEED 17

#define l_wifi CWifiHandler::Instance()

// Player states
typedef enum
{
  PLAYER_STATE_PLAYING = 0,
  PLAYER_STATE_WIN,
  PLAYER_STATE_LOSE
}
T_PLAYER_STATE;

typedef pair<u8, u8> typecard;

#endif  // DEFINE_H_
