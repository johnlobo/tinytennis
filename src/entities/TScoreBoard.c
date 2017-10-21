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
#include "../text/text.h"
#include "TMatch.h"

void printScoreBoard(u8 x, u8 y, TMatch *match){
	u8 *pvideo;

	pvideo = cpct_getScreenPtr(SCR_VMEM, x, y);
	cpct_drawSolidBox(SCR_VMEM, cpct_px2byteM0(4,4), 38, 20);
	pvideo = cpct_getScreenPtr(SCR_VMEM, x + 1, y + 2);
    cpct_drawSolidBox(pvideo, #0, 36, 16);
    drawText("PLAYER 1", x+2,y+3,0);
    drawText("PLAYER 2", x+2,y+9,0);
}