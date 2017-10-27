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
#include "TMatch.h"
#include "../text/text.h"


//////////////////////////////////////////////////////////////////
// initGame
//
//  initializes the whole program
//
// Returns:
//    void
//
void initMatchGame(TMatch *match){
    match->game.points[0] = 0;
    match->game.points[1] = 0;
    match->game.finished = 0;
}

//////////////////////////////////////////////////////////////////
// intiMatch
//
//  initializes the whole program
//
// Returns:
//    void
//
void initMatch(TMatch *match){
    u8 i;

    match->playersName[0][0] = '/0';
    match->playersName[1][0] = '/0';
    
    for (i=0; i<5; i++){
        match->sets[i].games[0] = 0;
        match->sets[i].games[1] = 0;
        match->sets[i].finished = 0; 
    }
    
    match->numberOfSets = 0;
    match->currentSet = 0;
    match->finished = 0;
    
    initMatchGame(match);
    
}

//////////////////////////////////////////////////////////////////
// createMatch
//
//  initializes the whole program
//
// Returns:
//    void
//
void createMatch(u8 nSets, u8 *player1Name, u8 *player2Name, TMatch *match){
    initMatch(match);
    
    strCopy(player1Name, (u8*) match->playersName[0]);
    strCopy(player2Name, (u8*) match->playersName[1]);
    
    match->numberOfSets = nSets;
    
    match->finished = 0;
}

//////////////////////////////////////////////////////////////////
// addPoint
//
//  initializes the whole program
//
// Returns:
//    
//
void addPoint(u8 player1, TMatch *match){
    u8 player2 = !player1;
    
    if (match->game.finished){
        initMatchGame(match);
    }
    match->game.points[player1]++;
    if ((match->game.points[player1]>4) ||
       ((match->game.points[player1]>3) && (match->game.points[player2]<3))){  // GAME WON
            match->sets[match->currentSet].games[player1]++;
            if ((match->sets[match->currentSet].games[player1]>5) && ((match->sets[match->currentSet].games[player1] - match->sets[match->currentSet].games[player2]>1))){ // SET WON
                match->currentSet++;
                if (match->currentSet >= match->numberOfSets){ // MATCH WON
                    match->finished = 1;
                    match->winner = player1;
                }
            }
        }
}