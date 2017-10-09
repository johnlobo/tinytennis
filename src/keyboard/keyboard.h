#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

//-----------------------------LICENSE NOTICE------------------------------------
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.
//------------------------------------------------------------------------------

#include <cpctelera.h>

typedef struct
{
    cpct_keyID up;
    cpct_keyID down;
    cpct_keyID left;
    cpct_keyID right;
    cpct_keyID fire1;
    cpct_keyID fire2;
    cpct_keyID pause;
    cpct_keyID abort;
    cpct_keyID music;
} TKeys;


u32 wait4UserKeypress();
cpct_keyID waitForAKey();
void waitKeyUp(cpct_keyID key);
u32 wait4Key(cpct_keyID key);
cpct_keyID redefineKey(u8 *text);
u8 checkKeys(const cpct_keyID *k, u8 numk);
void initKeys(TKeys *keys);


#endif