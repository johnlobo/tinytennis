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
#include "TPlayer.h"
#include "../util/util.h"
#include "../sprites/player1.h"
#include "../sprites/player2.h"
#include "TBall.h"
#include "../util/video.h"
#include "../levels/court01.h"
#include "../ai/ai.h"
#include "keyboard/keyboard.h"

const TPlayer tempPlayer1 =
{

    {   1
        ,   { 40, 40 }
        ,   { 160, 160 }
        ,   40 * SCALE, 160 * SCALE, 0
        ,   PLAYER_WIDTH, PLAYER_HEIGHT
        ,   &g_frames[0][0]
        ,   1
    }
    ,   0
    ,   M_up
    ,   GM_play
    ,   ST_stopped
    ,   SD_down
    ,   0
    ,   0, 0
    , {
        128, 256, 255, 255
    }
    , 0
    , 0, 0
    , 0, 0
};

const TFrame g_frames[2][PLAYER_FRAMES] = {
    {
        { sp_player1_00 },  { sp_player1_01 }
        ,  { sp_player1_02 },  { sp_player1_03 }
        ,  { sp_player1_04 },  { sp_player1_05 }
        ,  { sp_player1_06 },  { sp_player1_07 }
        ,  { sp_player1_08 },  { sp_player1_09 }
        ,  { sp_player1_10 },  { sp_player1_11 }
        ,  { sp_player1_12 },  { sp_player1_13 }
        ,  { sp_player1_14 },  { sp_player1_15 }
        ,  { sp_player1_16 },  { sp_player1_17 }
    },
    {
        { sp_player2_00 },  { sp_player2_01 }
        ,  { sp_player2_02 },  {  sp_player2_03 }
        ,  { sp_player2_04 },  {  sp_player2_05 }
        ,  { sp_player2_06 },  {  sp_player2_07 }
        ,  { sp_player2_08 },  {  sp_player2_09 }
        ,  { sp_player2_10 },  {  sp_player2_11 }
        ,  { sp_player2_12 },  {  sp_player2_13 }
        ,  { sp_player2_14 },  {  sp_player2_15 }
        ,  { sp_player2_16 },  {  sp_player2_17 }
    }
};

// Global Variables
TFrame *const anim_walking_right[2][WALKING_FRAMES] = {
    {&g_frames[0][1], &g_frames[0][2], &g_frames[0][3], &g_frames[0][1]},
    {&g_frames[1][1], &g_frames[1][2], &g_frames[1][3], &g_frames[1][1] }
};

TFrame *const anim_walking_left[2][WALKING_FRAMES] = {
    {&g_frames[0][4], &g_frames[0][5], &g_frames[0][6], &g_frames[0][4]},
    {&g_frames[1][4], &g_frames[1][5], &g_frames[1][6], &g_frames[1][4] }
};

TFrame *const anim_up[2][UP_FRAMES] = {
    {&g_frames[0][10], &g_frames[0][0], &g_frames[0][11], &g_frames[0][0]},
    {&g_frames[1][10], &g_frames[1][0], &g_frames[1][11], &g_frames[1][0] }
};

TFrame *const anim_down[2][DOWN_FRAMES] = {
    {&g_frames[0][12], &g_frames[0][13], &g_frames[0][14], &g_frames[0][13]},
    {&g_frames[1][12], &g_frames[1][13], &g_frames[1][14], &g_frames[1][13] }
};

TFrame *const anim_hittingUp[2][HITTING_FRAMES] = {
    {&g_frames[0][2], &g_frames[0][7], &g_frames[0][8], &g_frames[0][9], &g_frames[0][0]},
    {&g_frames[1][2], &g_frames[1][7], &g_frames[1][8], &g_frames[1][9], &g_frames[1][0]}
};

TFrame *const anim_hittingDown[2][HITTING_FRAMES] = {
    {&g_frames[0][5], &g_frames[0][15], &g_frames[0][16], &g_frames[0][17], &g_frames[0][12]},
    {&g_frames[1][5], &g_frames[1][15], &g_frames[1][16], &g_frames[1][17], &g_frames[1][12]}
};

TFrame *const anim_hittingBackUp[2][HITTING_FRAMES] = {
    {&g_frames[0][5], &g_frames[0][9], &g_frames[0][8], &g_frames[0][7], &g_frames[0][0]},
    {&g_frames[1][5], &g_frames[1][9], &g_frames[1][8], &g_frames[1][7], &g_frames[1][0]}
};

TFrame *const anim_hittingBackDown[2][HITTING_FRAMES] = {
    {&g_frames[0][2], &g_frames[0][17], &g_frames[0][16], &g_frames[0][15], &g_frames[0][12]},
    {&g_frames[1][2], &g_frames[1][17], &g_frames[1][16], &g_frames[1][15], &g_frames[1][12]}
};

void initPlayer1(TPlayer *player)
{
    cpct_memcpy(player, &tempPlayer1, sizeof(TPlayer));
}

void assignFrame(TFrame **animation, TPlayer *player, u8 pause)
{
    player->e.frame = animation[player->nframe / pause];
}

void selectSpritePlayer(TPlayer *player, u8 ai)
{
    switch (player->state)
    {
    case ST_stopped:
    case ST_AIstopped:
    {
        if (player->side == SD_down)
        {
            player->e.frame = &g_frames[ai][0];
        }
        else
        {
            player->e.frame = &g_frames[ai][12];
        }
        break;
    }
    case ST_walking:
    case ST_AImovingToTarget:
    {
        if (player->look == M_up)
        {
            assignFrame(anim_up[ai], player, ANIM_PAUSE);
        }
        else if (player->look == M_down)
        {
            assignFrame(anim_down[ai], player, ANIM_PAUSE);
        }
        else if (player->look == M_right)
        {
            assignFrame(anim_walking_right[ai], player, ANIM_PAUSE);
        } else {
            assignFrame(anim_walking_left[ai], player, ANIM_PAUSE);
        }
        break;
    }
    case ST_hitting:
    {
        if (player->look == M_up)
        {
            assignFrame(anim_hittingUp[ai], player, ANIM_HIT_PAUSE);
        }
        else
        {
            assignFrame(anim_hittingDown[ai], player, ANIM_HIT_PAUSE);
        }
        break;
    }
    case ST_hitting_back:
    {
        if (player->look == M_up)
        {
            assignFrame(anim_hittingBackUp[ai], player, ANIM_HIT_PAUSE);
        }
        else
        {
            assignFrame(anim_hittingBackDown[ai], player, ANIM_HIT_PAUSE);
        }
        break;
    }
    case ST_AIhitting:
    {
        assignFrame(anim_hittingDown[ai], player, ANIM_HIT_PAUSE);
        break;
    }
    }
}

void moveRight(TPlayer *player, i16 step)
{
    if ((((player->e.x[0] + player->e.w) * SCALE) + step) < (WIDTH * SCALE))
    {
        player->e.rx += step;
        player->e.x[0] = player->e.rx / SCALE;
        player->look  = M_right;
        player->e.draw = 1;
    }
}

void moveLeft(TPlayer *player, i16 step)
{
    if ((player->e.rx - step) > (160 * SCALE))
    {
        player->e.rx = 0;
        player->e.x[0] = 0;
    }
    else
    {
        player->e.rx -= step;
        player->e.x[0] = player->e.rx / SCALE;
    }
    player->look  = M_left;
    player->e.draw = 1;
}

void moveUp(TPlayer *player, i16 step)
{
    if (((player->e.ry - step) > (200 * SCALE)) && (player->side == SD_up)) {
        player->e.ry = 0;
        player->e.y[0] = 0;
    }
    else if (((player->e.ry - step) < (80 * SCALE)) && (player->side == SD_down)) {
        player->e.ry = 80 * SCALE;
        player->e.y[0] = 80;   
    }    
    else
    {
        player->e.ry -= step;
        player->e.y[0] = player->e.ry / SCALE;
    }
    player->e.draw = 1;
}

void moveDown(TPlayer *player, i16 step)
{
    if (((((player->e.y[0] + player->e.h) * SCALE) + step) > (HEIGHT * SCALE)) && (player->side == SD_down)){
        player->e.ry = (HEIGHT - player->e.h) * SCALE;
        player->e.y[0] = HEIGHT - player->e.h;
        player->e.draw = 1;
    } else if (((((player->e.y[0] + player->e.h) * SCALE) + step) > (80 * SCALE)) && (player->side == SD_up)){
        player->e.ry = (80 - player->e.h) * SCALE;
        player->e.y[0] = 80 - player->e.h;
        player->e.draw = 1;
    }
    else{
        player->e.ry += step;
        player->e.y[0] = player->e.ry / SCALE;
        player->e.draw = 1;
    }
}

void hitting_enter(TPlayer *player, TBall *ball)
{
    if (player->e.x[0] < ball->e.x[0]) {
        player->state = ST_hitting;
    } else {
        player->state = ST_hitting_back;
    }
    player->hit  =  HITTING_FRAMES * ANIM_HIT_PAUSE;
    player->hitDirH = 0;
    player->hitDirV = 0;
    player->nframe = 0;
    player->e.draw = 1;
}



void walking_enter(u8 look, TPlayer *player)
{
    player->nframe = 0;
    player->state = ST_walking;
    player->look   = look;
    player->e.draw = 1;
}

void stopped_enter(TPlayer *player)
{
    player->state = ST_stopped;
    if (player->side == SD_down) {
        player->look = M_up;
    } else {
        player->look = M_down;
    }
    player->e.draw = 1;
}

void hitting_animate(TPlayer *player)
{
    if (++player->nframe == HITTING_FRAMES * ANIM_HIT_PAUSE)
    {
        player->nframe = 0;
    }
    player->e.draw = 1;
}

void hitting(TPlayer *player, TKeys *keys)
{
    if ((cpct_isKeyPressed(Joy0_Right) || cpct_isKeyPressed(keys->right)) && (player->hitDirH < MAX_DIR_H)) {
        player->hitDirH+=2;
    }else if ((cpct_isKeyPressed(Joy0_Left) || cpct_isKeyPressed(keys->left)) && (player->hitDirH > MIN_DIR_H)) {
        player->hitDirH-=2;
    }
    
    if (player->hit > 0)
    {
        player->hit--;
        hitting_animate(player);
    }
    else
    {
        stopped_enter(player);
    }
}

void serving_enter(TPlayer *player)
{
    player->state = ST_hitting;
    player->hit  =  HITTING_FRAMES;
    player->e.draw = 1;
}


void serving_animate(TPlayer *player)
{
    if (++player->nframe == HITTING_FRAMES * ANIM_PAUSE)
    {
        player->nframe = 0;
    }
    player->e.draw = 1;
}

void serving(TPlayer *player)
{
    if (player->hit > 1)
    {
        player->hit--;
        serving_animate(player);
    }
    else
    {
        stopped_enter(player);
    }
}

void stopped(TPlayer *player, TPlayer *playerAI, TBall *ball, TKeys *keys)
{
    if ((cpct_isKeyPressed(Joy0_Up) || cpct_isKeyPressed(keys->up)) && (cpct_isKeyPressed(Joy0_Right) || cpct_isKeyPressed(keys->right)))
    {
        walking_enter(M_right, player);
    }
    else if ((cpct_isKeyPressed(Joy0_Up) || cpct_isKeyPressed(keys->up)) && (cpct_isKeyPressed(Joy0_Left) || cpct_isKeyPressed(keys->left)))
    {
        walking_enter(M_left, player);
    }
    else if ((cpct_isKeyPressed(Joy0_Down) || cpct_isKeyPressed(keys->down)) && (cpct_isKeyPressed(Joy0_Right) || cpct_isKeyPressed(keys->right)))
    {
        walking_enter(M_right, player);
    }
    else if ((cpct_isKeyPressed(Joy0_Down) || cpct_isKeyPressed(keys->down)) && (cpct_isKeyPressed(Joy0_Left) || cpct_isKeyPressed(keys->left)))
    {
        walking_enter(M_left, player);
    }
    else if ((player->phase == GM_play) && (cpct_isKeyPressed(Joy0_Up) || cpct_isKeyPressed(keys->up)))
    {
        walking_enter(M_up, player);
    }
    else if ((player->phase == GM_play) && (cpct_isKeyPressed(Joy0_Down) || cpct_isKeyPressed(keys->down)))
    {
        walking_enter(M_down, player);
    }
    else if (cpct_isKeyPressed(Joy0_Right) || cpct_isKeyPressed(keys->right))
    {
        walking_enter(M_right, player);
    }
    else if (cpct_isKeyPressed(Joy0_Left) || cpct_isKeyPressed(keys->left))
    {
        walking_enter(M_left, player);
    }
    else if (cpct_isKeyPressed(Joy0_Fire1) || cpct_isKeyPressed(keys->fire1))
    {
        if (player->phase == GM_play){
            if (player->side == SD_down) {
                player->look = M_up;
            } else {
                player->look = M_down;
            }
            hitting_enter(player, ball);
        }
        else{
            serving_enter(player);
        }
    }
    else if (cpct_isKeyPressed(Joy0_Fire2) || cpct_isKeyPressed(keys->fire2))
    {
        waitKeyUp(keys->fire2);
        newBall(playerAI->e.x[0] + (playerAI->e.w / 2), playerAI->e.y[0] + (playerAI->e.h), ball);
        //setAITarget(ball->bouncex, ball->bouncey, playerAI);
    }
}


void walking_animate(u8 look, TPlayer *player)
{
    player->look  = look;
    if (++player->nframe == WALKING_FRAMES * ANIM_PAUSE)
        player->nframe = 0;
    player->e.draw = 1;
}

void up_animate(TPlayer *player)
{
    if (++player->nframe == UP_FRAMES * ANIM_PAUSE)
        player->nframe = 0;
    player->e.draw = 1;
}

void down_animate(TPlayer *player)
{
    if (++player->nframe == DOWN_FRAMES * ANIM_PAUSE)
        player->nframe = 0;
    player->e.draw = 1;
}

void walking(TPlayer *player, TBall *ball, TKeys *keys)
{
    u8 moved = 0;
    if ((cpct_isKeyPressed(Joy0_Up) || cpct_isKeyPressed(keys->up)) && (cpct_isKeyPressed(Joy0_Right) || cpct_isKeyPressed(keys->right)))
    {
        moveUp(player, player->car.speedY);
        moveRight(player, player->car.speedX);
        walking_animate(M_right, player);
        moved = 1;
    }
    else if (cpct_isKeyPressed(Joy0_Up) || (cpct_isKeyPressed(keys->up)) && (cpct_isKeyPressed(Joy0_Left) || cpct_isKeyPressed(keys->left)))
    {
        moveUp(player, player->car.speedY);
        moveLeft(player, player->car.speedX);
        walking_animate(M_left, player);
        moved = 1;
    }
    else if ((cpct_isKeyPressed(Joy0_Down) || cpct_isKeyPressed(keys->down)) && (cpct_isKeyPressed(Joy0_Right) || cpct_isKeyPressed(keys->right)))
    {
        moveDown(player, player->car.speedY);
        moveRight(player, player->car.speedX);
        walking_animate(M_right, player);
        moved = 1;
    }
    else if (cpct_isKeyPressed(Joy0_Down) || (cpct_isKeyPressed(keys->down)) && (cpct_isKeyPressed(Joy0_Left) || cpct_isKeyPressed(keys->left)))
    {
        moveDown(player, player->car.speedY);
        moveLeft(player, player->car.speedX);
        moved = 1;
    }
    else if ((player->phase == GM_play) && (cpct_isKeyPressed(Joy0_Up) || cpct_isKeyPressed(keys->up)))
    {
        moveUp(player, player->car.speedY);
        up_animate(player);
        moved = 1;
    }
    else if ((player->phase == GM_play) && (cpct_isKeyPressed(Joy0_Down) || cpct_isKeyPressed(keys->down)))
    {
        moveDown(player, player->car.speedY);
        down_animate(player);
        moved = 1;
    }
    else if (cpct_isKeyPressed(Joy0_Right) || cpct_isKeyPressed(keys->right))
    {
        moveRight(player, player->car.speedX);
        walking_animate(M_right, player);
        moved = 1;
    }
    else if (cpct_isKeyPressed(Joy0_Left) || cpct_isKeyPressed(keys->left))
    {
        moveLeft(player, player->car.speedX);
        walking_animate(M_left, player);
        moved = 1;
    }
    if (cpct_isKeyPressed(Joy0_Fire1) || cpct_isKeyPressed(keys->fire1))
    {
        if (player->side == SD_down) {
            player->look = M_up;
        } else {
            player->look = M_down;
        }
        hitting_enter(player, ball);
        moved = 1;
    }
    if (cpct_isKeyPressed(Joy0_Fire2) || cpct_isKeyPressed(keys->fire2))
    {
        waitKeyUp(keys->fire2);
        newBall(40 * SCALE, 40 , ball);
        moved = 1;
    }
    if (!moved)
    {
        stopped_enter(player);
    }
}


void preparing(TPlayer *player, TKeys *keys)
{
    if (cpct_isKeyPressed(Joy0_Right) || cpct_isKeyPressed(keys->right))
    {
        moveRight(player, player->car.speedX);
        walking_animate(M_right, player);
    }
    else if (cpct_isKeyPressed(Joy0_Left) || cpct_isKeyPressed(keys->left))
    {
        moveLeft(player, player->car.speedX);
        walking_animate(M_left, player);
    }
    else if (cpct_isKeyPressed(Joy0_Fire1) || cpct_isKeyPressed(keys->fire1))
    {
        serving_enter(player);
    }
    else
    {
        stopped_enter(player);
    }
}


void executeState(TPlayer *player, TPlayer *playerAI, TBall *ball, TKeys *keys)
{
    switch (player->state)
    {
    case ST_stopped:
        stopped(player, playerAI, ball, keys);
        break;
    case ST_walking:
        walking(player, ball, keys);
        break;
    case ST_hitting:
    case ST_hitting_back:
        hitting(player, keys);
        break;
    case ST_preparing:
        preparing(player, keys);
        break;
    case ST_serving:
        serving(player);
        break;
    }
}
