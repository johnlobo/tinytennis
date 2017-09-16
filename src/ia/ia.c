#include "ia.h"
#include "../defines.h"
#include "../entities/TPlayer.h"
#include "../sprites/player1.h"
#include "../util/util.h"

const TPlayer tempIAPlayer =
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
	,	ST_IAStopped
	, {
		255, 512, 255, 255 // Character definition

	}
	, 0, 0  // targetX and targetY
	, 0, 0	// stepX and stepY
};

void initIAPlayer(TPlayer *player) {
	cpct_memcpy(player, &tempIAPlayer, sizeof(TPlayer));
}

void IAHitting(TPlayer *player, TBall *ball) {
}

void IAMovingToTarget(TPlayer *player, TBall *ball) {
	u8 posX, posY;

	posX = player->e.x[0] / SCALE;
	posY = player->e.y[0] / SCALE;

	if (hasReachedTarget(&player->e, player->targetX, player->targetY, player->stepX, player->stepY)) {
		player->iaState = ST_IAStopped;
	} else {
		if (posX < player->targetX) {
			moveRight(player, player->stepX);
			walking_animate(M_right, player);
		} else if (posX > player->targetX) {
			moveLeft(player, player->stepX);
			walking_animate(M_left, player);
		}
		if (posY < player->targetY) {
			moveDown(player, player->stepY);
			down_animate(player);
		} else {
			moveUp(player, player->stepY);
			up_animate(player);
		}
		player->e.draw = 1;
	}
}


void setIATarget(u8 x, u8 y, TPlayer *player){
	i16 distX, distY;
	i16 t, stX, stY;

	player->targetX = x;
	player->targetY = y;
	// Calculate the steps to target
	distX = x - player->e.x[0];  	//distance X
	distY = y - player->e.y[0];  	//distance Y
	t = max((fast_abs(distX)/player->car.speedX), (fast_abs(distY)/player->car.speedY));  // # of steps
	stX = distX / t; 			// size of step X
	stY = distY / t;			// size of step Y
	// Set the steps to target 
	if (player->car.speedX<stX){
		player->stepX = player->car.speedX;
	}else{
		player->stepX = stX;
	}
	if (player->car.speedY<stY){
		player->stepY = player->car.speedY;
	}else{
		player->stepY = stY;
	}
	// Set IA state
	player->iaState = ST_IAMovingToTarget;
}

void IAStopped(TPlayer *player, TBall *ball)
{
	if (!hasReachedTarget(&player->e, TARGET_CENTER_X, TARGET_CENTER_Y, player->stepX, player->stepY) && (ball->vy < 0)) {
		player->targetX = TARGET_CENTER_X;
		player->targetY = TARGET_CENTER_Y;
		player->state = ST_walking;
	} else if (ball->vy < 0) {
		player->targetX = ball->bouncex + ball->vx;
		player->targetY = ball->bouncey + ball->vy;
		player->state = ST_walking;
	}
}

void executeStateIA(TPlayer *player, TBall *ball)
{
	switch (player->iaState)
	{
	case ST_IAStopped:
		IAStopped(player, ball);
		break;
	case ST_IAMovingToTarget:
		IAMovingToTarget(player, ball);
		break;
	case ST_IAHitting:
		IAHitting(player, ball);
		break;
	}
}