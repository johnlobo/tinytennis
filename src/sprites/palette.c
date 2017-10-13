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
#include "../util/util.h"


// Standard palette of the CPC
const u8 colours[27] = { 0x54, 0x44, 0x55, 0x5C, 0x58, 0x5D, 0x4C, 0x45, 0x4D, 0x56, 0x46, 0x57,
                         0x5E, 0x40, 0x5F, 0x4E, 0x47, 0x4F, 0x52, 0x42, 0x53, 0x5A, 0x59, 0x5B,
                         0x4A, 0x43, 0x4B};

u8 palette_aux[16];
u8 i, j;

void initpalette(u8 *palette){
    //u8 i;
    
    for (i=0; i<16; i++){
        palette[i] = 0;
    }
}

void copyPalette(u8 *paletteIN, u8 *paletteOUT){
    //u8 i;
    
    for (i=0;i<16;i++){

        paletteOUT[i] = paletteIN[i];
    }
}

void fadeIn(u8 *palette){
    //u8 i, j;
    //u8 palette_aux[16];
    
    initpalette(&palette_aux[0]);
    for (i=0; i<27; i++){
        for (j=0; j<16; j++){
            if (palette_aux[j] != palette[j]){
                palette_aux[j] = colours[i];
            }
        }
        cpct_setPalette(palette_aux, 16);
    }
}

void fadeOut(u8 *palette){
    //u8 i, j;
    //u8 palette_aux[16];
    
    copyPalette(palette, &palette_aux[0]);
    
    for (i=27; i>0; i--){
        for (j=0; j<16; j++){
            if (palette_aux[j] == colours[i]){
                palette_aux[j] = colours[i-1];
            }
        }
        cpct_setPalette(palette_aux, 16);
        //delay(20);
    }
}

void fadeOut2(u8 *palette){
    copyPalette(palette, &palette_aux[0]);
    
    for (i=15; i>=0; i--){
        palette_aux[i] = 0x54;
        cpct_setPalette(palette_aux, 16);
        delay(10);
    }
}

void setBlankpalette(){
    //u8 palette_aux[16];
    
    initpalette(&palette_aux[0]);
    cpct_setPalette(palette_aux, 16);
}
