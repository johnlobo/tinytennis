#include "TPlayer.h"
#include <cpctelera.h>
#include "../main.h"
#include "../util/util.h"
#include "../sprites/player1.h"
#include "TBall.h"

// Looking to
enum {
    M_right   = 0
    ,  M_left
} ELook;

// Player States
enum {
    ST_stopped  = 0
    ,  ST_walking
    ,  ST_hitting
} EStates;

const TFrame g_frames[PLAYER_FRAMES] = {
	{ M_right, sp_player1_00 },  { M_right, sp_player1_01 }
	,  { M_right, sp_player1_02 },  { M_right, sp_player1_03 }
	,  { M_right, sp_player1_04 },  { M_right, sp_player1_05 }
	,  { M_right, sp_player1_06 },  { M_right, sp_player1_07 }
	,  { M_right, sp_player1_08 },  { M_right, sp_player1_09 }
};

// Global Variables
TFrame* const anim_walking[WALKING_FRAMES] = {&g_frames[1], &g_frames[2], &g_frames[3], &g_frames[1] };
TFrame* const anim_hitting[HITTING_FRAMES] = {&g_frames[7], &g_frames[8], &g_frames[9], &g_frames[8], &g_frames[7]};


void initPlayer(TPlayer *player){
	player->x = player->px = 40 * SCALE;
    player->y = player->py = 100 * SCALE;
    player->state = ST_stopped;
    player->look   = M_right;
    player->nframe = 0;
    player->frame  = &g_frames[0];
    player->moved = 1;
}

void assignFrame(TFrame **animation, TPlayer *player) {
	player->frame = animation[player->nframe / ANIM_PAUSE];
}

void turnFrame(TPlayer *player) {
	TFrame* f = player->frame;
	if (f->look != player->look) {
		cpct_hflipSpriteM0(PLAYER_WIDTH, PLAYER_HEIGHT, f->sprite);
		f->look = player->look;
	}
}
void selectSpritePlayer(TPlayer *player) {
	switch (player->state) {
	case ST_stopped: {
		player->frame = &g_frames[0];
		break;
	}
	case ST_walking: {
		assignFrame(anim_walking, player);
		turnFrame(player);
		break;
	}
	case ST_hitting: {
		assignFrame(anim_hitting, player);
		break;
	}
	}
}

void moveRight(TPlayer *player) {
	if (((player->x / SCALE) + PLAYER_WIDTH + 1) < WIDTH) {
		player->x += 1 * SCALE;
		player->look  = M_right;
	}
	player->moved = 1;
}

void moveLeft(TPlayer *player) {
	if ((player->x / SCALE) > 0) {
		player->x -= 1 * SCALE;
		player->look  = M_left;
	}
	player->moved = 1;
}

void moveUp(TPlayer *player) {
	if ((player->y / SCALE) - VERTICAL_STEP > 0) {
		player->y -= VERTICAL_STEP * SCALE;
		//player->look  = M_right;
	}
	player->moved = 1;
}

void moveDown(TPlayer *player) {
	if (((player->y / SCALE) + PLAYER_HEIGHT + VERTICAL_STEP) < HEIGHT) {
		player->y += VERTICAL_STEP * SCALE;
		//player->look  = M_right;
	}
	player->moved = 1;
}

void drawPlayer(TPlayer *player) {
	u8* pvmem;
	i32 posx, posy;
	posx = player->x / SCALE;
	posy = player->y / SCALE;
	if (((posx + PLAYER_WIDTH) < WIDTH) && ((posy + PLAYER_HEIGHT) < HEIGHT)) {
		pvmem = cpct_getScreenPtr((u8*) CPCT_VMEM_START, posx, posy);
		cpct_drawSpriteMaskedAlignedTable(player->frame->sprite, pvmem, PLAYER_WIDTH, PLAYER_HEIGHT, g_tablatrans);
	}
}

void erasePlayer(TPlayer *player) {
	u8* pvmem;
	i32 posx, posy;
	posx = player->px / SCALE;
	posy = player->py / SCALE;
	if (((posx + PLAYER_WIDTH) < WIDTH) && ((posy + PLAYER_HEIGHT) < HEIGHT)) {
		pvmem = cpct_getScreenPtr((u8*) CPCT_VMEM_START, posx, posy);
		cpct_drawSolidBox(pvmem, #0,PLAYER_WIDTH, PLAYER_HEIGHT);
	}
}

void redrawPlayer(TPlayer *player) {
	erasePlayer(player);
	drawPlayer(player);
}

void hitting_enter(TPlayer *player, TBall *ball) {
	player->state = ST_hitting;
	player->hit  =  HITTING_FRAMES;
	player->moved = 1;
	newBall(player->x, player->y, ball);
}



void walking_enter(u8 look, TPlayer *player) {
	player->nframe = 0;
	player->state = ST_walking;
	player->look   = look;
	player->moved = 1;
}

void stopped_enter(TPlayer *player) {
	player->state = ST_stopped;
	player->moved = 1;
}

void hitting_animate(TPlayer *player) {
	if (++player->nframe == HITTING_FRAMES * ANIM_PAUSE) {
		player->nframe = 0;
	}
	player->moved = 1;
}

void hitting(TPlayer *player) {
	if (player->hit > 1) {
		player->hit--;
		delay(5);
		hitting_animate(player);
	} else {
		stopped_enter(player);
	}
}

void stopped(TPlayer *player, TBall *ball, TKeys *keys) {
	if (cpct_isKeyPressed(keys->up)) {
		walking_enter(player->look, player);
	} else if (cpct_isKeyPressed(keys->down)) {
		walking_enter(player->look, player);
	} else if (cpct_isKeyPressed(keys->right)) {
		walking_enter(M_right, player);
	} else if (cpct_isKeyPressed(keys->left)) {
		walking_enter(M_left, player);
	} else if (cpct_isKeyPressed(keys->fire)) {
		hitting_enter(player, ball);
	}

}



void walking_animate(u8 look, TPlayer *player) {
	player->look  = look;
	if (++player->nframe == WALKING_FRAMES * ANIM_PAUSE)
		player->nframe = 0;
	player->moved = 1;
}

void walking(TPlayer *player, TBall *ball, TKeys *keys) {
	if (cpct_isKeyPressed(keys->up)) {
		moveUp();
	} else if (cpct_isKeyPressed(keys->down)) {
		moveDown();
	} else if (cpct_isKeyPressed(keys->right)) {
		moveRight();
		walking_animate(M_right, player);
	} else if (cpct_isKeyPressed(keys->left)) {
		moveLeft();
		walking_animate(M_left, player);
	} else if (cpct_isKeyPressed(keys->fire)) {
		hitting_enter(player, ball);
	} else {
		stopped_enter(player);
	}
}

void executeState(TPlayer *player, TBall *ball, TKeys *keys) {
	switch (player->state) {
	case ST_stopped:
		stopped(player, ball, keys);
		break;
	case ST_walking:
		walking(player, ball, keys);
		break;
	case ST_hitting:
		hitting(player);
		break;
	}
}
