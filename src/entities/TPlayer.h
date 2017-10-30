//-----------------------------LICENSE NOTICE------------------------------------
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU Lesser General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.
//------------------------------------------------------------------------------

#ifndef _TPLAYER_H_
#define _TPLAYER_H_

#include <types.h>
#include "../defines.h"
#include "TBall.h"
#include "../util/util.h"
#include "../keyboard/keyboard.h"

#define MAX_DIR_H 9
#define MIN_DIR_H -10

#define PLAYER_WIDTH   SP_PLAYER1_00_W
#define PLAYER_HEIGHT   SP_PLAYER1_00_H

// Sprites States
#define PLAYER_FRAMES   18
// Animaciones
#define ANIM_PAUSE      8
#define ANIM_HIT_PAUSE  4
#define WALKING_FRAMES  4
#define UP_FRAMES       4
#define DOWN_FRAMES     4
#define HITTING_FRAMES  5

typedef struct
{
    i16 speedX, speedY;
    i16 accuracy;
    i16 offense;
} TCharacter;

typedef struct
{
    TEntity e;
    i16 hstep, vstep;
    u8 nframe;
    ELook look;
    u8 phase;
    EStates state;
    ESides side;
    u8 hit;
    i8 hitDirH;
    i8 hitDirV;
    TCharacter car;
    u8 onTarget;
    u8 targetX, targetY;
    i16 stepX, stepY;
} TPlayer;


extern const TFrame g_frames[2][PLAYER_FRAMES];
extern TFrame *const anim_walking[2][WALKING_FRAMES];
extern TFrame *const anim_hitting[2][HITTING_FRAMES];

extern TPlayer player;

void initPlayer1(TPlayer *player);
void initPlayer2(TPlayer *player);
void selectSpritePlayer(TPlayer *player, u8 ai);
void moveUp(TPlayer *player, i16 step);
void moveDown(TPlayer *player, i16 step);
void moveRight(TPlayer *player, i16 step);
void moveLeft(TPlayer *player, i16 step);
void up_animate(TPlayer *player);
void down_animate(TPlayer *player);
void walking_animate(u8 look, TPlayer *player);
void hitting_animate(TPlayer *player);
void executeState(TPlayer *player, TPlayer *playerIA, TBall *ball, TKeys *keys);

#endif