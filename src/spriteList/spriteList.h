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

#ifndef _SPRITELIST_H_
#define _SPRITELIST_H_

#define MAX_SPRITE_LIST 10

#include "../defines.h"

typedef struct {
	u8 count;
    TEntity *list[MAX_SPRITE_LIST];
} TSpriteList;
    
extern void print_sprites();

void initSpriteList();
void addSprite(TEntity *e);
void deleteSprite(u8 id, u8 erase);
void orderSpriteList();
void printSprites();

#endif

