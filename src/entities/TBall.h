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


#ifndef _TBALL_H_
#define _TBALL_H_

#include <types.h>
#include "../defines.h"

#define BALL_WIDTH SP_BALL_0_W
#define BALL_HEIGHT SP_BALL_0_H
#define SHADOW_BALL_WIDTH SP_BALL_1_W
#define SHADOW_BALL_HEIGHT SP_BALL_1_H

typedef struct
{
    TEntity e;
    TEntity e_ball;
    u8 turn;
    i16 vx, vy, vz;
    u8 bouncex, bouncey;
    u8 nBounces;
    u8 active;
} TBall;

extern TBall ball;

void updateBall(TBall *ball);
void initBall(TBall *ball);
void newBall(u8 x, u8 y, TBall *ball);
void calcBounce(TBall *ball);

#endif