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
        ,   { 40 * SCALE, 40 * SCALE }
        , 	{ 160 * SCALE, 160 * SCALE }
        , 	{ 0, 0 }
        ,	PLAYER_WIDTH, PLAYER_HEIGHT
        ,	&g_frames[0][0]    
        ,	1
    }
    ,   256, 512
    ,   0
    ,   M_up
    ,	GM_play
    ,	ST_stopped
    ,	SD_down
    ,	0
    , {
        255, 512, 255, 255
    }
    , 0, 0
    , 0, 0
};

const TFrame g_frames[2][PLAYER_FRAMES] ={
{
    { M_right, sp_player1_00 },  { M_right, sp_player1_01 }
    ,  { M_right, sp_player1_02 },  { M_right, sp_player1_03 }
    ,  { M_right, sp_player1_04 },  { M_right, sp_player1_05 }
    ,  { M_right, sp_player1_06 },  { M_right, sp_player1_07 }
    ,  { M_right, sp_player1_08 },  { M_right, sp_player1_09 }
    ,  { M_right, sp_player1_10 },  { M_right, sp_player1_11 }
    ,  { M_right, sp_player1_12 },  { M_right, sp_player1_13 }
    ,  { M_right, sp_player1_14 },
},
{
    { M_right, sp_player2_00 },  { M_right, sp_player2_01 }
    ,  { M_right, sp_player2_02 },  { M_right, sp_player2_03 }
    ,  { M_right, sp_player2_04 },  { M_right, sp_player2_05 }
    ,  { M_right, sp_player2_06 },  { M_right, sp_player2_07 }
    ,  { M_right, sp_player2_08 },  { M_right, sp_player2_09 }
    ,  { M_right, sp_player2_10 },  { M_right, sp_player2_11 }
    ,  { M_right, sp_player2_12 },  { M_right, sp_player2_13 }
    ,  { M_right, sp_player2_14 },
}};

// Global Variables
TFrame *const anim_walking[2][WALKING_FRAMES] = {
                    {&g_frames[0][1], &g_frames[0][2], &g_frames[0][3], &g_frames[0][1]},
                    {&g_frames[1][1], &g_frames[1][2], &g_frames[1][3], &g_frames[1][1] }};

TFrame *const anim_up[2][UP_FRAMES] = {
                    {&g_frames[0][10], &g_frames[0][0], &g_frames[0][11], &g_frames[0][0]},
                    {&g_frames[1][10], &g_frames[1][0], &g_frames[1][11], &g_frames[1][0] }};

TFrame *const anim_down[2][DOWN_FRAMES] = {
                    {&g_frames[0][12], &g_frames[0][13], &g_frames[0][14], &g_frames[0][13]},
                    {&g_frames[1][12], &g_frames[1][13], &g_frames[1][14], &g_frames[1][13] }};

TFrame *const anim_hittingUp[2][HITTING_FRAMES] = {
                    {&g_frames[0][7], &g_frames[0][8], &g_frames[0][9], &g_frames[0][8],	&g_frames[0][7]},
                    {&g_frames[1][7], &g_frames[1][8], &g_frames[1][9], &g_frames[1][8], &g_frames[1][7]}};

TFrame *const anim_hittingDown[2][HITTING_FRAMES] = {
                    {&g_frames[0][7], &g_frames[0][8], &g_frames[0][9], &g_frames[0][8], &g_frames[0][7]},
                    {&g_frames[1][7], &g_frames[1][8], &g_frames[1][9], &g_frames[1][8],   &g_frames[1][7]}};

TFrame *const anim_hittinBackUp[2][HITTING_FRAMES] = {
                    {&g_frames[0][9], &g_frames[0][8], &g_frames[0][7], &g_frames[0][8], &g_frames[0][9]},
                    {&g_frames[1][7], &g_frames[1][8], &g_frames[1][9], &g_frames[1][8], &g_frames[1][7]}};

TFrame *const anim_hittingBackDown[2][HITTING_FRAMES] = {
                    {&g_frames[0][7], &g_frames[0][8], &g_frames[0][9], &g_frames[0][8], &g_frames[0][7]},
                    {&g_frames[1][7], &g_frames[1][8], &g_frames[1][9], &g_frames[1][8],   &g_frames[1][7]}};

void initPlayer1(TPlayer *player)
{
    cpct_memcpy(player, &tempPlayer1, sizeof(TPlayer));
}

void assignFrame(TFrame **animation, TPlayer *player, u8 pause)
{
    player->e.frame = animation[player->nframe / pause];
}

void turnFrame(TPlayer *player)
{
    TFrame *f = player->e.frame;
    if (f->look != player->look)
    {
        cpct_hflipSpriteM0(player->e.w, player->e.h, f->sprite);
        f->look = player->look;
    }
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
        else
        {
            assignFrame(anim_walking[ai], player, ANIM_PAUSE);
            turnFrame(player);
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
    case ST_AIhitting:
    {
        assignFrame(anim_hittingDown[ai], player, ANIM_HIT_PAUSE);
        break;
    }
    }
}

void moveRight(TPlayer *player, i16 step)
{
    if ((player->e.x[0] + (player->e.w * SCALE) + step) < (WIDTH * SCALE))
    {
        player->e.x[0] += step;
        player->look  = M_right;
        player->e.draw = 1;
    }
}

void moveLeft(TPlayer *player, i16 step)
{
    if ((player->e.x[0] - step) > (160 * SCALE))
    {
        player->e.x[0] = 0;
    }
    else
    {
        player->e.x[0] -= step;
    }
    player->look  = M_left;
    player->e.draw = 1;

}

void moveUp(TPlayer *player, i16 step)
{
    if ((player->e.y[0] - step) > (200 * SCALE))
    {
        player->e.y[0] = 0;
    }
    else
    {
        player->e.y[0] -= step;
    }
    //player->look  = M_right;
    player->look = M_up;
    player->e.draw = 1;

}

void moveDown(TPlayer *player, i16 step)
{
    if ((player->e.y[0] + (player->e.h * SCALE) + step) < (HEIGHT * SCALE))
    {
        player->e.y[0] += step;
        //player->look  = M_right;
        player->look = M_down;
        player->e.draw = 1;
    }
}

void hitting_enter(TPlayer *player)
{
    player->state = ST_hitting;
    player->hit  =  HITTING_FRAMES * ANIM_HIT_PAUSE;
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

void hitting(TPlayer *player)
{
    if (player->hit > 1)
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
    if ((cpct_isKeyPressed(keys->up)) && (cpct_isKeyPressed(keys->right)))
    {
        walking_enter(M_right, player);
    }
    else if ((cpct_isKeyPressed(keys->up)) && (cpct_isKeyPressed(keys->left)))
    {
        walking_enter(M_left, player);
    }
    else if ((cpct_isKeyPressed(keys->down)) && (cpct_isKeyPressed(keys->right)))
    {
        walking_enter(M_right, player);
    }
    else if ((cpct_isKeyPressed(keys->down)) && (cpct_isKeyPressed(keys->left)))
    {
        walking_enter(M_left, player);
    }
    else if ((player->phase == GM_play) && (cpct_isKeyPressed(keys->up)))
    {
        walking_enter(player->look, player);
    }
    else if ((player->phase == GM_play) && (cpct_isKeyPressed(keys->down)))
    {
        walking_enter(player->look, player);
    }
    else if (cpct_isKeyPressed(keys->right))
    {
        walking_enter(M_right, player);
    }
    else if (cpct_isKeyPressed(keys->left))
    {
        walking_enter(M_left, player);
    }
    else if (cpct_isKeyPressed(keys->fire1))
    {
        if (player->phase == GM_play)
            hitting_enter(player);
        else
            serving_enter(player);
    }
    else if (cpct_isKeyPressed(keys->fire2))
    {
        waitKeyUp(keys->fire2);
        newBall(40 * SCALE, 0 , ball);
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

void walking(TPlayer *player, TPlayer *playerAI, TBall *ball, TKeys *keys)
{
    u8 moved = 0;
    if ((cpct_isKeyPressed(keys->up)) && (cpct_isKeyPressed(keys->right)))
    {
        moveUp(player, player->vstep);
        moveRight(player, player->hstep);
        walking_animate(M_right, player);
        moved = 1;
    }
    else if ((cpct_isKeyPressed(keys->up)) && (cpct_isKeyPressed(keys->left)))
    {
        moveUp(player, player->vstep);
        moveLeft(player, player->hstep);
        walking_animate(M_left, player);
        moved = 1;
    }
    else if ((cpct_isKeyPressed(keys->down)) && (cpct_isKeyPressed(keys->right)))
    {
        moveDown(player, player->vstep);
        moveRight(player, player->hstep);
        walking_animate(M_right, player);
        moved = 1;
    }
    else if ((cpct_isKeyPressed(keys->down)) && (cpct_isKeyPressed(keys->left)))
    {
        moveDown(player, player->vstep);
        moveLeft(player, player->hstep);
        moved = 1;
    }
    else if ((player->phase == GM_play) && (cpct_isKeyPressed(keys->up)))
    {
        moveUp(player, player->vstep);
        up_animate(player);
        moved = 1;
    }
    else if ((player->phase == GM_play) && (cpct_isKeyPressed(keys->down)))
    {
        moveDown(player, player->vstep);
        down_animate(player);
        moved = 1;
    }
    else if (cpct_isKeyPressed(keys->right))
    {
        moveRight(player, player->hstep);
        walking_animate(M_right, player);
        moved = 1;
    }
    else if (cpct_isKeyPressed(keys->left))
    {
        moveLeft(player, player->hstep);
        walking_animate(M_left, player);
        moved = 1;
    }
    if (cpct_isKeyPressed(keys->fire1))
    {
        hitting_enter(player);
        moved = 1;
    }
    if (cpct_isKeyPressed(keys->fire2))
    {
        //newBall(player->e.x[0], player->e.y[0], ball);
        waitKeyUp(keys->fire2);
        newBall(40 * SCALE, 0 , ball);
        //setAITarget(ball->bouncex, ball->bouncey, playerAI);
        moved = 1;
    }
    if (!moved)
    {
        stopped_enter(player);
    }
}


void preparing(TPlayer *player, TKeys *keys)
{
    if (cpct_isKeyPressed(keys->right))
    {
        moveRight(player, player->hstep);
        walking_animate(M_right, player);
    }
    else if (cpct_isKeyPressed(keys->left))
    {
        moveLeft(player, player->hstep);
        walking_animate(M_left, player);
    }
    else if (cpct_isKeyPressed(keys->fire1))
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
        walking(player, playerAI, ball, keys);
        break;
    case ST_hitting:
        hitting(player);
        break;
    case ST_preparing:
        preparing(player, keys);
        break;
    case ST_serving:
        serving(player);
        break;
    }
}
