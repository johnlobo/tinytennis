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

TMatch match;

//////////////////////////////////////////////////////////////////
// initGame
//
//  initializes the whole program
//
// Returns:
//    void
//
void initGame(){
    match.game.points[0] = 0;
    match.game.points[1] = 0;
    match.game.finished = 0;
}

//////////////////////////////////////////////////////////////////
// intiMatch
//
//  initializes the whole program
//
// Returns:
//    void
//
void initMatch(){
    u8 i;

    match.playersName[0][0] = '/0';
    match.playersName[1][0] = '/0';
    
    for (i=0; i<5; i++){
        match.sets[i].games[0] = 0;
        match.sets[i].games[1] = 0;
        match.sets[i].finished = 0; 
    }
    
    match.numberOfSets = 0;
    match.currentSet = 0;
    match.finished = 0;
    
    initGame();
    
}

//////////////////////////////////////////////////////////////////
// createMatch
//
//  initializes the whole program
//
// Returns:
//    void
//
void createMatch(u8 nSets, u8 *player1Name, u8 *player2Name){
    initMatch();
    
    strCopy(player1Name, &match.playersName[0]);
    strCopy(player2Name, &match.playersName[1]);
    
    match.numberOfSets = nSets;
}

//////////////////////////////////////////////////////////////////
// addPoint
//
//  initializes the whole program
//
// Returns:
//    void
//
u8 addPoint(u8 player){
    if (match.game.finished){
        initGame();
    }
    match.game.points[player]++;
    if ((match.game.points[player]>4) ||
       ((match.game.points[player]>3) && (match.game.points[!(player)]<3)){
           match.game.finished = 1;
           return 1;
        }
    return 0;
}