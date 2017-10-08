//-----------------------------LICENSE NOTICE------------------------------------
//
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

#ifndef _MENU_H_
#define _MENU_H_

#define MAX_HEIGHT 10
#define ICON_W 2
#define ICON_H 4


#include <cpctelera.h>

typedef struct{
	u8 selectedOption;
	u8 height;
	i8 vy;
	u8 *sprite;
	u8 *shadowSprite;
} TIcon;

void initIcon(TIcon *icon);
void deleteIcon(TIcon *icon);
void drawIcon(TIcon *icon);
void drawMenu();
void updateIcon(TIcon *icon);

#endif 