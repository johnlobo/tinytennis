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

const TPlayer tempPlayer1 =
{

    {   { 40 * SCALE, 40 * SCALE }
        , 	{ 170 * SCALE, 170 * SCALE }
        , 	{ 0, 0 }
        ,	PLAYER_WIDTH, PLAYER_HEIGHT
        ,   256, 512
        ,	&g_frames[0][0]
        ,	0
        ,	M_right
        ,	2
    }
    ,	GM_play
    ,	ST_stopped
    ,	SD_down
    ,	0
    , {
        255, 512, 255, 255, 255, 255

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
TFrame *const anim_walking[2][WALKING_FRAMES] = {{&g_frames[0][1], &g_frames[0][2], &g_frames[0][3], &g_frames[0][1]},
                    {&g_frames[1][1], &g_frames[1][2], &g_frames[1][3], &g_frames[1][1] }};
TFrame *const anim_up[2][UP_FRAMES] = {{&g_frames[0][10], &g_frames[0][0], &g_frames[0][11], &g_frames[0][0]},
                    {&g_frames[1][10], &g_frames[1][0], &g_frames[1][11], &g_frames[1][0] }};
TFrame *const anim_down[2][DOWN_FRAMES] = {{&g_frames[0][12], &g_frames[0][13], &g_frames[0][14], &g_frames[0][13]},
                    {&g_frames[1][12], &g_frames[1][13], &g_frames[1][14], &g_frames[1][13] }};
TFrame *const anim_hittingUp[2][HITTING_FRAMES] = {{&g_frames[0][7], &g_frames[0][8], &g_frames[0][9], &g_frames[0][8],	&g_frames[0][7]},
                    {&g_frames[1][7], &g_frames[1][8], &g_frames[1][9], &g_frames[1][8], &g_frames[1][7]}};
TFrame *const anim_hittingDown[2][HITTING_FRAMES] = {{&g_frames[0][7], &g_frames[0][8], &g_frames[0][9], &g_frames[0][8], &g_frames[0][7]},
                    {&g_frames[1][7], &g_frames[1][8], &g_frames[1][9], &g_frames[1][8],   &g_frames[1][7]}};

void initPlayer1(TPlayer *player)
{
    cpct_memcpy(player, &tempPlayer1, sizeof(TPlayer));
}

void assignFrame(TFrame **animation, TPlayer *player, u8 pause)
{
    player->e.frame = animation[player->e.nframe / pause];
}

void turnFrame(TPlayer *player)
{
    TFrame *f = player->e.frame;
    if (f->look != player->e.look)
    {
        cpct_hflipSpriteM0(player->e.w, player->e.h, f->sprite);
        f->look = player->e.look;
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
        if (player->e.look == M_up)
        {
            assignFrame(anim_up[ai], player, ANIM_PAUSE);
        }
        else if (player->e.look == M_down)
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
        assignFrame(anim_hittingUp[ai], player, ANIM_HIT_PAUSE);
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
        player->e.look  = M_right;
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
    player->e.look  = M_left;
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
    player->e.look = M_up;
    player->e.draw = 1;

}

void moveDown(TPlayer *player, i16 step)
{
    if ((player->e.y[0] + (player->e.h * SCALE) + step) < (HEIGHT * SCALE))
    {
        player->e.y[0] += step;
        //player->look  = M_right;
        player->e.look = M_down;
        player->e.draw = 1;
    }
}

void drawPlayer(TPlayer *player)
{
    u8 *pvmem;
    u8 posx, posy;
    posx = player->e.x[0] / SCALE;
    posy = player->e.y[0] / SCALE;
    //if (((posx + player->e.w) <= WIDTH) && ((posy + player->e.h) <= HEIGHT))
    //{
    pvmem = cpct_getScreenPtr((u8 *) g_scrbuffers[0], posx, posy);
    cpct_drawSpriteMaskedAlignedTable(player->e.frame->sprite, pvmem, player->e.w, player->e.h, g_tablatrans);
    //}
}

void erasePlayer(TPlayer *player)
{
    //u8 *pvmem;
    u8 posx, posy;
    posx = player->e.x[1] / SCALE;
    posy = player->e.y[1] / SCALE;
    /*if (((posx + player->e.w) <= WIDTH) && ((posy + player->e.h) <= HEIGHT)) {
    	pvmem = cpct_getScreenPtr((u8*) g_scrbuffers[1], posx, posy);
    	cpct_drawSolidBox(pvmem, #0,player->e.w, player->e.h);
    }*/
    if (((posx + player->e.w) <= WIDTH) && ((posy + player->e.h) <= HEIGHT))
    {
        cpct_etm_drawTileBox2x4 (posx / 2, posy / 4, (player->e.w / 2) + 1, (player->e.h / 4) + 1, MAP_WIDTH, g_scrbuffers[0], court);
    }

}

void hitting_enter(TPlayer *player)
{
    player->state = ST_hitting;
    player->hit  =  HITTING_FRAMES * ANIM_HIT_PAUSE;
    player->e.nframe = 0;
    player->e.draw = 1;
}



void walking_enter(u8 look, TPlayer *player)
{
    player->e.nframe = 0;
    player->state = ST_walking;
    player->e.look   = look;
    player->e.draw = 1;
}

void stopped_enter(TPlayer *player)
{
    player->state = ST_stopped;
    player->e.draw = 1;
}

void hitting_animate(TPlayer *player)
{
    if (++player->e.nframe == HITTING_FRAMES * ANIM_HIT_PAUSE)
    {
        player->e.nframe = 0;
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
    if (++player->e.nframe == HITTING_FRAMES * ANIM_PAUSE)
    {
        player->e.nframe = 0;
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
        walking_enter(player->e.look, player);
    }
    else if ((player->phase == GM_play) && (cpct_isKeyPressed(keys->down)))
    {
        walking_enter(player->e.look, player);
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
        //newBall(player->e.x[0], player->e.y[0], ball);
        newBall(40 * SCALE, 0 , ball);
        setAITarget(ball->bouncex, ball->bouncey, playerAI);
    }
}


void walking_animate(u8 look, TPlayer *player)
{
    player->e.look  = look;
    if (++player->e.nframe == WALKING_FRAMES * ANIM_PAUSE)
        player->e.nframe = 0;
    player->e.draw = 1;
}

void up_animate(TPlayer *player)
{
    if (++player->e.nframe == UP_FRAMES * ANIM_PAUSE)
        player->e.nframe = 0;
    player->e.draw = 1;
}

void down_animate(TPlayer *player)
{
    if (++player->e.nframe == DOWN_FRAMES * ANIM_PAUSE)
        player->e.nframe = 0;
    player->e.draw = 1;
}

void walking(TPlayer *player, TPlayer *playerAI, TBall *ball, TKeys *keys)
{
    u8 moved = 0;
    if ((cpct_isKeyPressed(keys->up)) && (cpct_isKeyPressed(keys->right)))
    {
        moveUp(player, player->e.vstep);
        moveRight(player, player->e.hstep);
        walking_animate(M_right, player);
        moved = 1;
    }
    else if ((cpct_isKeyPressed(keys->up)) && (cpct_isKeyPressed(keys->left)))
    {
        moveUp(player, player->e.vstep);
        moveLeft(player, player->e.hstep);
        walking_animate(M_left, player);
        moved = 1;
    }
    else if ((cpct_isKeyPressed(keys->down)) && (cpct_isKeyPressed(keys->right)))
    {
        moveDown(player, player->e.vstep);
        moveRight(player, player->e.hstep);
        walking_animate(M_right, player);
        moved = 1;
    }
    else if ((cpct_isKeyPressed(keys->down)) && (cpct_isKeyPressed(keys->left)))
    {
        moveDown(player, player->e.vstep);
        moveLeft(player, player->e.hstep);
        moved = 1;
    }
    else if ((player->phase == GM_play) && (cpct_isKeyPressed(keys->up)))
    {
        moveUp(player, player->e.vstep);
        up_animate(player);
        moved = 1;
    }
    else if ((player->phase == GM_play) && (cpct_isKeyPressed(keys->down)))
    {
        moveDown(player, player->e.vstep);
        down_animate(player);
        moved = 1;
    }
    else if (cpct_isKeyPressed(keys->right))
    {
        moveRight(player, player->e.hstep);
        walking_animate(M_right, player);
        moved = 1;
    }
    else if (cpct_isKeyPressed(keys->left))
    {
        moveLeft(player, player->e.hstep);
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
        newBall(40 * SCALE, 0 , ball);
        setAITarget(ball->bouncex, ball->bouncey, playerAI);
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
        moveRight(player, player->e.hstep);
        walking_animate(M_right, player);
    }
    else if (cpct_isKeyPressed(keys->left))
    {
        moveLeft(player, player->e.hstep);
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
