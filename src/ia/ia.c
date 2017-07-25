#include "ia.h"
#include "../entities/TPlayer.h"
#include "../sprites/player1.h"

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
	,	ST_IAstopped
	, {
		255, 512, 255, 255

	}
	, 0, 0
};

void initIAPlayer(TPlayer *player) {
	cpct_memcpy(player, &tempIAPlayer, sizeof(TPlayer));
}

void IAHitting(TPlayer *player, TBall *ball) {
}

void IAWalking(TPlayer *player, TBall *ball) {
	u8 posX, posY;

	posX = player->e.x[0] / SCALE;
	posY = player->e.y[0] / SCALE;

	if (hasReachedTarget(player->e, player->targetX, player->targetY)) {
		player->iaState = ST_stopped;
	} else {
		if (posX < player->targetX) {
			moveRight(player);
			walking_animate(M_right, player);
		} else if (posX > player->targetX) {
			moveLeft(player);
			walking_animate(M_left, player);
		}
		if (posY < player->targetY) {
			moveDown(player);
			down_animate(player);
		} else {
			moveUp(player);
			up_animate(player);
		}
		player->e.draw = 1;
	}
}


void IAStopped(TPlayer *player, TBall *ball)
{
	if ((!hasReachedTarget(player->e, TARGET_CENTER_X, TARGET_CENTER_Y) && (ball->vy < 0)) {
		player->targetX = TARGET_CENTER_X;
		player->targetY = TARGET_CENTER_Y;
		player->state = ST_walking;
	} else if (ball->vy > 0) {
		player->targetX = ball->bouncex + ball->vx;
		player->targetY = ball->bouncey + ball->vy;
		player->state = ST_walking;
	}
}

void executeStateIA(TPlayer *player, TBall *ball)
{
	switch (player->state)
	{
	case ST_stopped:
		IAStopped(player, ball);
		break;
	case ST_walking:
		IAWalking(player, ball);
		break;
	case ST_hitting:
		IAHitting(player, ball);
		break;
	}
}