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

#include <cpctelera.h>
#include "../defines.h"
#include "spriteList.h"

TSpriteList spriteList;

void initSpriteList(){
    cpct_memset(&spriteList, 0, sizeof(TSpriteList));
}

void addSprite(TEntity *e){
    u8 i;
    if (spriteList.count<MAX_SPRITE_LIST){
        i = 0;
        while ((i<MAX_SPRITE_LIST) && (spriteList.list[i]->id !=0 )){
            i++;
        }
        if (i<MAX_SPRITE_LIST){
            spriteList.count++;
            spriteList.list[i] = e;
        }
    }
    
}

void deleteSprite(u8 id){
    u8 i = 0;
    while ((i<MAX_SPRITE_LIST) && (spriteList.list[i]->id != id )){
        i++;
    }
    if (i<MAX_SPRITE_LIST){
        spriteList.count--;
        cpct_memset(&spriteList.list[i], 0, sizeof(TEntity));
    }
}

void orderList(){
    u8 i = 1;  // Begin with one to avoid to overflow the array
    TEntity *aux;
    if (spriteList.count > 1){
        while ((i<spriteList.count) && (spriteList.list[i]->y[0] > spriteList.list[i-1]->y[0])){
            i++;
        }
        if (i<spriteList.count){
            aux = spriteList.list[i];
            spriteList.list[i] = spriteList.list[i+1];
            spriteList.list[i+1] = aux;
        }
    }
}

void printSprites(){
    
}
