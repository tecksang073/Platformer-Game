/********************************************
Course : TGD2251 Game Physics
Session: Trimester 1, 2020/21
ID and Name #1 : 1161104534 Ho Teck Sang
Contacts #1 : 0126287073
********************************************/

#pragma once
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

class Player
{
public:
	enum Direction { pLeft = 0, pRight = 1, pJumpLeft = 2, pJumpRight = 3, pRunLeft = 4, pRunRight = 5 };
	Direction direc = pRight;
	int coinPoint;

private:
	b2Body* playerBody;
	b2Body* lastGround;

public:
	Player();
	b2Body* createPlayer(b2World* world, float X, float Y);
	bool isPlayerOnGround(b2Body* playerBody, b2Body* groundBody[], int groundBodyCon);
	void playerJump(b2Body* playerBody);
	void playerRightOnAir(b2Body* playerBody);
	void playerRight(b2Body* playerBody);
	void playerLeftOnAir(b2Body* playerBody);
	void playerLeft(b2Body* playerBody);
	void playerRightEnd(b2Body* playerBody);
	void playerLeftEnd(b2Body* playerBody);
};

