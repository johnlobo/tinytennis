//-----------------------------LICENSE NOTICE------------------------------------
//  This file is part of Outlaws
//  Copyright (C) 2016 RETROBYTES PRODUCTIONS
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

#include "video.h"

u8* const g_scrbuffers[2] = {SCR_VMEM, SCR_BUFF};

void forceFrontBuffer(u8** scrbuffers){

	scrbuffers[0] = SCR_BUFF;
	scrbuffers[1] = SCR_VMEM;

	cpct_setVideoMemoryPage( (u16)(scrbuffers[1]) >> 10 );

}

void swapBuffers(u8** scrbuffers) {
    
    u8* aux; // Auxiliary pointer for making the change
    
    cpct_setVideoMemoryPage( (u16)(scrbuffers[1]) >> 10 );
    
    aux = scrbuffers[0];
    scrbuffers[0] = scrbuffers[1];
    scrbuffers[1] = aux;
}
