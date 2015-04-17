#include "Player.h"

USING_NS_CC;

Player::Player(Size visiblesize, Vec2 origin) : myVisibleSize(visiblesize), myOrigin(origin)
{
	this->init();
}

Player::~Player()
{

}

bool Player::init()
{
	this->bodyPlayer = PhysicsBody::createBox(Size(27, 31), PhysicsMaterial(1.0f, 0.0f, 1.0f));
	this->bodyPlayer->setRotationEnable(false);
	this->bodyPlayer->setMass(10.0f);

	this->spritePlayer = Sprite::create("pictures/hero.png", Rect(223, 20, 28, 32));
	this->spritePlayer->setPosition(Vec2(this->myVisibleSize.width / 2 + this->myOrigin.x, this->myVisibleSize.height / 2 + this->myOrigin.y));
	this->spritePlayer->setAnchorPoint(Vec2(0, 0));
	this->spritePlayer->setScale(2.0f, 2.0f);

	this->bodyPlayer->setGravityEnable(true);

	this->spritePlayer->setPhysicsBody(this->bodyPlayer);

	return true;
}

void Player::update()
{
	
}

void Player::moveToLeft()
{
	this->spritePlayer->setPositionX(this->spritePlayer->getPositionX() - 2.0f);
}

void Player::moveToRight()
{
	this->spritePlayer->setPositionX(this->spritePlayer->getPositionX() + 2.0f);
}

void Player::resetVelocity()
{
	this->bodyPlayer->setVelocity(Vec2(0, 0));
}

void Player::jump()
{
	this->bodyPlayer->setVelocity(Vec2(0, 150));
}