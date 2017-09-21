#include "ai.h"
#include "../defines.h"
#include "../entities/TPlayer.h"
#include "../sprites/player1.h"
#include "../util/util.h"

const TPlayer tempAIPlayer =
{
	{	{ 40 * SCALE, 40 * SCALE }
		, 	{ 10 * SCALE, 10 * SCALE }
		, 	{ 0, 0 }
		,	PLAYER_WIDTH, PLAYER_HEIGHT
		,   256, 512
		,	&g_frames[12]
		,	0
		,	M_right
		,	2
	}
	,	GM_play
	,	ST_stopped
	,	SD_up
	,	0
	, {
		256, 512, 256, 256 // Character definition

	}
	, 0, 0  // targetX and targetY
	, 0, 0	// stepX and stepY
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

void AIhitting(TPlayer *player, TBall *ball)
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
	setAITarget(TARGET_CENTER_X, TARGET_CENTER_Y, player);
}

void AIhitting_enter(TPlayer *player)
{
	player->state = ST_AIhitting;
	player->hit  =  HITTING_FRAMES * ANIM_HIT_PAUSE;
	player->e.nframe = 0;
	player->e.draw = 1;
}

void AImovingToTarget(TPlayer *player, TBall *ball)
{
	u8 posX, posY;

	posX = player->e.x[0] / SCALE;
	posY = player->e.y[0] / SCALE;

	if (hasReachedTarget(&player->e, player->targetX, player->targetY, player->stepX, player->stepY))
	{
		AIstopped_enter(player);
	}
	else
	{
		if (posX < player->targetX)
		{
			moveRight(player, player->stepX);
			walking_animate(M_right, player);
		}
		else if (posX > player->targetX)
		{
			moveLeft(player, player->stepX);
			walking_animate(M_left, player);
		}
		if (posY > player->targetY)
		{
			moveDown(player, player->stepY);
			down_animate(player);
		}
		else
		{
			moveUp(player, player->stepY);
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
	player->targetX = x; 
	player->targetY = y;


	// Calculate the steps to target
	distX = (x * SCALE) - player->e.x[0];  	//distance X
	distY = (y * SCALE) - player->e.y[0];  	//distance Y
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
	player->e.nframe = 0;
	if (player->stepX > 0)
	{
		player->e.look = M_right;
	}
	else
	{
		player->e.look = M_left;
	}
	player->e.draw = 1;
	player->state = ST_AImovingToTarget;
}

void AIstopped(TPlayer *player, TBall *ball)
{
	if ((ball->vy < 0) && (distance(player->e.x[0], player->e.y[0], ball->e.x[0], ball->e.y[0]) < HIT_RANGE))
	{
		player->state = ST_AIhitting;
	}
	else if (ball->vy < 0)
	{
		setAITarget(ball->bouncex + ball->vx, ball->bouncey + ball->vy, player);
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
		AIhitting(player, ball);
		break;
	}
}