/********************************************
Course : TGD2251 Game Physics
Session: Trimester 1, 2020/21
ID and Name #1 : 1161104534 Ho Teck Sang
Contacts #1 : 0126287073
********************************************/

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include "Player.h"

// Constructor
Player::Player()
{
	coinPoint = 0;
}

// Jump function physics
void Player::playerJump(b2Body* playerBody)
{
	float karakterYon = playerBody->GetLinearVelocity().x;
	karakterYon = karakterYon - (karakterYon / 3);
	playerBody->SetLinearVelocity(b2Vec2(karakterYon, -9));

	if (karakterYon > 0) {
		direc = pJumpRight;
	}
	else if (karakterYon < 0) {
		direc = pJumpLeft;
	}

	if (lastGround->GetUserData() == (void*)1) {
		if (lastGround->GetType() == b2_kinematicBody) {
			lastGround->SetLinearVelocity(b2Vec2(0, +6));
		}
	}
}

// Mid-air physics function
void Player::playerRightOnAir(b2Body* playerBody)
{
	b2Vec2 vel = playerBody->GetLinearVelocity();
	float velChange = 3 - vel.x;
	float impulse = playerBody->GetMass() * velChange;
	playerBody->ApplyLinearImpulse(b2Vec2(impulse, 0), playerBody->GetWorldCenter(), true);
	direc = pJumpRight;
}

// Body face and move right physics function
void Player::playerRight(b2Body* playerBody)
{
	b2Vec2 vel = playerBody->GetLinearVelocity();
	float velChange = 5 - vel.x;
	float impulse = playerBody->GetMass() * velChange;
	playerBody->ApplyLinearImpulse(b2Vec2(impulse, 0), playerBody->GetWorldCenter(), true);
	direc = pRunRight;
}

// Mid-air face left physics function
void Player::playerLeftOnAir(b2Body* playerBody)
{
	b2Vec2 vel = playerBody->GetLinearVelocity();
	float velChange = -3 - vel.x;
	float impulse = playerBody->GetMass() * velChange;
	playerBody->ApplyLinearImpulse(b2Vec2(impulse, 0), playerBody->GetWorldCenter(), true);
	direc = pJumpLeft;
}

// Body face and move left physics function
void Player::playerLeft(b2Body* playerBody)
{
	b2Vec2 vel = playerBody->GetLinearVelocity();
	float velChange = -5 - vel.x;
	float impulse = playerBody->GetMass() * velChange;
	playerBody->ApplyLinearImpulse(b2Vec2(impulse, 0), playerBody->GetWorldCenter(), true);
	direc = pRunLeft;
}

// Body face right physics function
void Player::playerRightEnd(b2Body* playerBody)
{
	b2Vec2 vel = playerBody->GetLinearVelocity();
	float velChange = 0 - vel.x;
	float impulse = playerBody->GetMass() * velChange;
	playerBody->ApplyLinearImpulse(b2Vec2(impulse, 0), playerBody->GetWorldCenter(), true);
	direc = pRight;
}

// Body face left physics function
void Player::playerLeftEnd(b2Body* playerBody)
{
	b2Vec2 vel = playerBody->GetLinearVelocity();
	float velChange = 0 - vel.x;
	float impulse = playerBody->GetMass() * velChange;
	playerBody->ApplyLinearImpulse(b2Vec2(impulse, 0), playerBody->GetWorldCenter(), true);
	direc = pLeft;
}

// Initialize the player with physics
b2Body* Player::createPlayer(b2World* world, float X, float Y)
{
	b2BodyDef BodyDefK;
	BodyDefK.position = b2Vec2(X / 30.f, Y / 30.f);
	BodyDefK.type = b2_dynamicBody;
	b2Body* Body = world->CreateBody(&BodyDefK);

	b2PolygonShape ShapeK;
	ShapeK.SetAsBox((50.f / 2) / 30.f, (50.f / 2) / 30.f);
	b2FixtureDef FixtureDef;
	FixtureDef.density = 1.f;
	FixtureDef.friction = 0.7f;
	FixtureDef.shape = &ShapeK;
	Body->CreateFixture(&FixtureDef);
	return Body;
}

// Check if player is standing on the ground function
bool Player::isPlayerOnGround(b2Body* playerBody, b2Body* groundBody[], int groundBodyCon)
{
	for (int i = 0; i < groundBodyCon; i++) {
		float playerX = playerBody->GetPosition().x;
		float playerY = playerBody->GetPosition().y;
		float groundLeft{};
		float groundRight{};

		if (groundBody[i]->GetUserData() == (void*)4) {
			groundLeft = groundBody[i]->GetPosition().x - (100.f / 30.f);
			groundRight = groundBody[i]->GetPosition().x + (100.f / 30.f);
		}
		else if (groundBody[i]->GetUserData() == (void*)1) {
			groundLeft = groundBody[i]->GetPosition().x - (25.f / 30.f);
			groundRight = groundBody[i]->GetPosition().x + (25.f / 30.f);
		}

		float groundY = groundBody[i]->GetPosition().y;
		float playerGroundDif = groundY - playerY;

		if (playerX < groundRight && playerX > groundLeft && playerGroundDif > 1.5 && playerGroundDif < 1.7) {
			lastGround = groundBody[i];
			return true;
		}
	}
	return false;
}
