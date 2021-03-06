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

#ifndef _TDUST_H_
#define _TDUST_H_

#include <types.h>
#include "../defines.h"

#define DUST_WIDTH 2
#define DUST_HEIGHT 4
#define DUST_FRAMES 3
#define DUST_PAUSE 4


typedef struct {
    TEntity e;
    u8 nFrame;
    u8 active;
} TDust;

typedef struct {
    u8 nDusts;
    TDust dustList[5];
}TDustList;

void initDustList();
void createDust(u8 x, u8 y);
void updateDusts();

#endif
