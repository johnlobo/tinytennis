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

#ifndef _AI_H_
#define _AI_H_

#include "../defines.h"
#include "../entities/TPlayer.h"
#include "../entities/TBall.h"

#define TARGET_CENTER_X 40
#define TARGET_CENTER_Y 0

#define HIT_RANGE PLAYER_HEIGHT * 2 * SCALE

void initAIPlayer(TPlayer *player);
void setAITarget(u8 x, u8 y, TPlayer *player);
void executeStateAI(TPlayer *player, TBall *ball);

#endif