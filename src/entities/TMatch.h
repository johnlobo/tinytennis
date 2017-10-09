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

#ifndef _TMATCH_H_
#define _TMATCH_H_

typedef struct {
    u8 points[2];
    u8 finished;
} TGame;

typedef struct {
    u8 games[2];
    u8 finished;
} TSet;

typedef struct {
    u8 playersName[2][20];
    TSet sets[5];
    TGame game;
    u8 numberOfSets;
    u8 currentSet;
    u8 finished;
} TMatch;

#endif