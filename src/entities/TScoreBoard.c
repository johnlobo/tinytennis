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

const u8 pointsText[5][4] = {
            {" 0\0"}, {"15\0"}, {"30\0"}, {"40\0"}, {" A\0"}
		};

void printScoreBoard(u8 x, u8 y, TMatch *match){
	u8 *pvideo;
	u8 i;

	pvideo = cpct_getScreenPtr(SCR_VMEM, x, y);
	cpct_drawSolidBox(pvideo, cpct_px2byteM0(4,4), 38, 20);
	pvideo = cpct_getScreenPtr(SCR_VMEM, x + 1, y + 2);
    cpct_drawSolidBox(pvideo, #0, 36, 16);
    drawText((u8*) &match->playersName[0], x+2,y+3,0);
    drawText((u8*) &match->playersName[1], x+2,y+9,0);
	drawText((u8*) &pointsText[match->game.points[0]],x+22,y+3, 0);
	drawText((u8*) &pointsText[match->game.points[1]],x+22,y+9 ,0
		);
	for (i=0; i<match->numberOfSets; i++){
		drawNumber(match->sets[i].games[0],1,x+28+(i*3),y+3);
		drawNumber(match->sets[i].games[1],1,x+28+(i*3),y+9);
	}
	
}