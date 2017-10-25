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

#ifndef _TBALLMACHINE_H_
#define _TBALLMACHINE_H_

#include <cpctelera.h>
#include "../defines.h"
#include "../entities/TBall.h"


typedef struct{
    u8 x,y;
    u8 w,h;
    u8 angle;
    u8 speed;
    i8 dir;
} TCannon;

typedef struct{
    u8 x,y;
    u8 w,h;
    TCannon c;
    u8 ballSpped;
    u8 active;
} TBallMachine;

void initBallMachine();
void createBallMachine(u8 x, u8 y);
void activateBallMachine();
void deActivateBallMachine();
void updateBallMachine(TBall *ball);

#endif