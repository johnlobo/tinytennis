#include <cpctelera.h>
#include "../defines.h"
#include "TPlayer.h"
#include "../util/util.h"
#include "../sprites/player1.h"
#include "TBall.h"
#include "../util/video.h"
#include "../levels/court01.h"

const TPlayer tempPlayer1 =
{

	{	{ 40 * SCALE, 40 * SCALE }
		, 	{ 170 * SCALE, 170 * SCALE }
		, 	{ 0, 0 }
		,	PLAYER_WIDTH, PLAYER_HEIGHT
		,   256, 512
		,	&g_frames[0]
		,	0
		,	M_right
		,	2
	}
	,	GM_play
	,	ST_stopped
	,	SD_down
	,	0
	,	ST_IAstopped
	, {
		255, 512, 255, 255

	}
	, 0, 0
};

const TFrame g_frames[PLAYER_FRAMES] =
{
	{ M_right, sp_player1_00 },  { M_right, sp_player1_01 }
	,  { M_right, sp_player1_02 },  { M_right, sp_player1_03 }
	,  { M_right, sp_player1_04 },  { M_right, sp_player1_05 }
	,  { M_right, sp_player1_06 },  { M_right, sp_player1_07 }
	,  { M_right, sp_player1_08 },  { M_right, sp_player1_09 }
	,  { M_right, sp_player1_10 },  { M_right, sp_player1_11 }
	,  { M_right, sp_player1_12 },  { M_right, sp_player1_13 }
	,  { M_right, sp_player1_14 },
};

// Global Variables
TFrame *const anim_walking[WALKING_FRAMES] = {&g_frames[1], &g_frames[2], &g_frames[3], &g_frames[1] };
TFrame *const anim_up[UP_FRAMES] = {&g_frames[10], &g_frames[0], &g_frames[11], &g_frames[0] };
TFrame *const anim_down[DOWN_FRAMES] = {&g_frames[12], &g_frames[13], &g_frames[14], &g_frames[13] };
TFrame *const anim_hitting[HITTING_FRAMES] = {&g_frames[7], &g_frames[8], &g_frames[9], &g_frames[8], &g_frames[7]};


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
void selectSpritePlayer(TPlayer *player)
{
	switch (player->state)
	{
	case ST_stopped:
	{
		if (player->side == SD_down)
		{
			player->e.frame = &g_frames[0];
		}
		else
		{
			player->e.frame = &g_frames[12];
		}
		break;
	}
	case ST_walking:
	{
		if (player->e.look == M_up)
		{
			assignFrame(anim_up, player, ANIM_PAUSE);
		}
		else if (player->e.look == M_down)
		{
			assignFrame(anim_down, player, ANIM_PAUSE);
		}
		else
		{
			assignFrame(anim_walking, player, ANIM_PAUSE);
			turnFrame(player);
		}
		break;
	}
	case ST_hitting:
	{
		assignFrame(anim_hitting, player, ANIM_HIT_PAUSE);
		break;
	}
	}
}

void moveRight(TPlayer *player)
{
	if ((player->e.x[0] + (player->e.w * SCALE) + player->e.hstep) < (WIDTH * SCALE))
	{
		player->e.x[0] += player->e.hstep;
		player->e.look  = M_right;
		player->e.draw = 1;
	}
}

void moveLeft(TPlayer *player)
{
	if (player->e.x[0] - player->e.hstep > (160*SCALE)) {
		player->e.x[0] = 0;
	} else {
		player->e.x[0] -= player->e.hstep;
	}
	player->e.look  = M_left;
	player->e.draw = 1;

}

void moveUp(TPlayer *player)
{
	if (player->e.y[0] - player->e.vstep > (200*SCALE)) {
		player->e.y[0] = 0;
	} else {
		player->e.y[0] -= player->e.vstep;
	}
	//player->look  = M_right;
	player->e.look = M_up;
	player->e.draw = 1;

}

void moveDown(TPlayer *player)
{
	if ((player->e.y[0] + (player->e.h * SCALE) + player->e.vstep) < (HEIGHT * SCALE))
	{
		player->e.y[0] += player->e.vstep;
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
	player->hit  =  HITTING_FRAMES;
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
	if (++player->e.nframe == HITTING_FRAMES * ANIM_PAUSE)
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
		delay(5);
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
		delay(5);
		serving_animate(player);
	}
	else
	{
		stopped_enter(player);
	}
}

void stopped(TPlayer *player, TBall *ball, TKeys *keys)
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
	} else if ((player->phase == GM_play) && (cpct_isKeyPressed(keys->up)))
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
		newBall(player->e.x[0], player->e.y[0], ball);
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

void walking(TPlayer *player, TBall *ball, TKeys *keys)
{
	if ((cpct_isKeyPressed(keys->up)) && (cpct_isKeyPressed(keys->right)))
	{
		moveUp(player);
		moveRight(player);
		walking_animate(M_right, player);
	}
	else if ((cpct_isKeyPressed(keys->up)) && (cpct_isKeyPressed(keys->left)))
	{
		moveUp(player);
		moveLeft(player);
		walking_animate(M_left, player);
	}
	else if ((cpct_isKeyPressed(keys->down)) && (cpct_isKeyPressed(keys->right)))
	{
		moveDown(player);
		moveRight(player);
		walking_animate(M_right, player);
	}
	else if ((cpct_isKeyPressed(keys->down)) && (cpct_isKeyPressed(keys->left)))
	{
		moveDown(player);
		moveLeft(player);
	}
	else if ((player->phase == GM_play) && (cpct_isKeyPressed(keys->up)))
	{
		moveUp(player);
		up_animate(player);
	}
	else if ((player->phase == GM_play) && (cpct_isKeyPressed(keys->down)))
	{
		moveDown(player);
		down_animate(player);
	}
	else if (cpct_isKeyPressed(keys->right))
	{
		moveRight(player);
		walking_animate(M_right, player);
	}
	else if (cpct_isKeyPressed(keys->left))
	{
		moveLeft(player);
		walking_animate(M_left, player);
	}
	else if (cpct_isKeyPressed(keys->fire1))
	{
		hitting_enter(player);
	}
	else if (cpct_isKeyPressed(keys->fire2))
	{
		newBall(player->e.x[0], player->e.y[0], ball);
	}
	else
	{
		stopped_enter(player);
	}
}


void preparing(TPlayer *player, TKeys *keys)
{
	if (cpct_isKeyPressed(keys->right))
	{
		moveRight(player);
		walking_animate(M_right, player);
	}
	else if (cpct_isKeyPressed(keys->left))
	{
		moveLeft(player);
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


void executeState(TPlayer *player, TBall *ball, TKeys *keys)
{
	switch (player->state)
	{
	case ST_stopped:
		stopped(player, ball, keys);
		break;
	case ST_walking:
		walking(player, ball, keys);
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
