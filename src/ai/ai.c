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

#include "ai.h"
#include "../defines.h"
#include "../entities/TPlayer.h"
#include "../sprites/player1.h"
#include "../util/util.h"

const TPlayer tempAIPlayer =
{

	{	2
		,   { 40, 40 }
		, 	{ 0, 0 }
		, 	{ 0, 0 }
	 	,   40 * SCALE, 0, 0
		,	PLAYER_WIDTH, PLAYER_HEIGHT
		,	&g_frames[1][12]
		,	1
	}
	,   256, 512
	,   0
	,   M_down
	,	GM_play
	,	ST_AIstopped
	,	SD_up
	,	0
	,	0, 0
	, {
		255, 512, 255, 255 // Character definition

	}
	, 0
	, 0, 0 // targetX and targetY
	, 0, 0 // stepX and stepY
};

void initAIPlayer(TPlayer *player)
{
	cpct_memcpy(player, &tempAIPlayer, sizeof(TPlayer));
}

void AIstopped_enter(TPlayer *player)
{
	player->state = ST_AIstopped;
	player->e.draw = 1;
}

void AIhitting(TPlayer *player)
{
	if (player->hit > 1)
	{
		player->hit--;
		delay(5);  //  ??????????????????????????????????????????????????????????????????????????????
		hitting_animate(player);
	}
	else
	{
		AIstopped_enter(player);
	}
}

void AIhitting_enter(TPlayer *player)
{
	player->state = ST_AIhitting;
	player->hit  =  HITTING_FRAMES * ANIM_HIT_PAUSE;
	player->nframe = 0;
	player->e.draw = 1;
}

void AImovingToTarget(TPlayer *player, TBall *ball)
{
	if (hasReachedTarget(&player->e, player->targetX, player->targetY, player->stepX, player->stepY))
	{
		player->onTarget = 1;
		AIstopped_enter(player);
	}
	else
	{
		if (player->e.x[0] < player->targetX)
		{
			moveRight(player, player->stepX);
			walking_animate(M_right, player);
		}
		else if (player->e.x[0] > player->targetX)
		{
			moveLeft(player, player->stepX * -1);
			walking_animate(M_left, player);
		}
		if (player->e.y[0] < player->targetY)
		{
			moveDown(player, player->stepY);
			down_animate(player);
		}
		else
		{
			moveUp(player, player->stepY * -1);
			up_animate(player);
		}
		player->e.draw = 1;
	}
}


void setAITarget(u8 x, u8 y, TPlayer *player)
{
	i16 distX, distY;
	i16 t, stX, stY;
	if (x > 200) {
		x = 0; //Left bound
	} else if (x > 79) {
		x = 79; //Right bound
	}
	if (y > 220) {
		y = 0; //Upper bound
	} else if (y > 90) {
		y = 90; //Right bound
	}
	if ((player->e.x[0] != x) && (player->e.y[0] != y)) {
		player->targetX = x;
		player->targetY = y;
		// Calculate the steps to target
		distX = x - player->e.x[0];  	//distance X
		distY = y - player->e.y[0];  	//distance Y
		t = max((fast_abs(distX) / player->car.speedX), (fast_abs(distY) / player->car.speedY)); // # of steps
		stX = distX / t; 			// size of step X
		stY = distY / t;			// size of step Y
		// Set the steps to target
		if (player->car.speedX < fast_abs(stX))
		{
			player->stepX = player->car.speedX * sign(stX);
		}
		else
		{
			player->stepX = stX;
		}
		if (player->car.speedY < fast_abs(stY))
		{
			player->stepY = player->car.speedY * sign(stY);
		}
		else
		{
			player->stepY = stY;
		}
		// Set AI state
		player->nframe = 0;
		if (player->stepX > 0)
		{
			player->look = M_right;
		}
		else
		{
			player->look = M_left;
		}
		player->onTarget = 0;
		player->e.draw = 1;
		player->state = ST_AImovingToTarget;
	} else {
		player->onTarget = 1;
		AIstopped_enter(player);
	}
}

void AIstopped(TPlayer *player, TBall *ball)
{
	if (ball->turn == 2) {
		if (player->onTarget == 0) {
			setAITarget(ball->bouncex + ball->vx, ball->bouncey + ( 2 * ball->vy), player);
		} else if (distance(player->e.x[0], player->e.y[0], ball->e.x[0], ball->e.y[0]) < HIT_RANGE) {
			AIhitting_enter(player);
		}
	} else if (ball->turn == 1) {
		if (player->onTarget == 0) {
			setAITarget(TARGET_CENTER_X, TARGET_CENTER_Y, player);
		}
	}
}

void executeStateAI(TPlayer *player, TBall *ball)
{
	switch (player->state)
	{
	case ST_AIstopped:
		AIstopped(player, ball);
		break;
	case ST_AImovingToTarget:
		AImovingToTarget(player, ball);
		break;
	case ST_AIhitting:
		AIhitting(player);
		break;
	}
}
