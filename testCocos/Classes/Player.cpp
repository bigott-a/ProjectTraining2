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
	// set all texture
	this->initSprite = Sprite::create("pictures/heroInit.png");

	// init first sprite
	this->spritePlayer = Sprite::create();
	this->changeSprite(this->initSprite);
	//this->spritePlayer->setAnchorPoint(Vec2(0, 0));
	this->spritePlayer->setPosition(Vec2(this->myVisibleSize.width / 2 + this->myOrigin.x, this->myVisibleSize.height / 2 + this->myOrigin.y));
	this->spritePlayer->setScale(SCALE_PLAYER, SCALE_PLAYER);

	// set PhysicsBody
	this->bodyPlayer = PhysicsBody::createBox(/*this->spritePlayer->getContentSize()*/Size(29.0f, 33.0f) * SCALE_PLAYER);
	this->bodyPlayer->setRotationEnable(false);
	this->bodyPlayer->setGravityEnable(true);

	// set Physicsbody to our player
	this->spritePlayer->setPhysicsBody(this->bodyPlayer);

	return true;
}

void Player::changeSprite(Sprite *newSprite)
{
	this->spritePlayer->setTexture(newSprite->getTexture());
	this->spritePlayer->setTextureRect(newSprite->getTextureRect());
	this->lookHeroRight = true;
}


void Player::update()
{
	if ((this->bodyPlayer->getVelocity().x > 10 && this->lookHeroRight == false)
		|| (this->bodyPlayer->getVelocity().x < -10 && this->lookHeroRight == true))
		this->changeLook();
}

void Player::changeLook()
{
	this->lookHeroRight = !this->lookHeroRight;
	this->spritePlayer->setFlipX(!this->spritePlayer->isFlipX());
}

void Player::moveToLeft()
{
	this->bodyPlayer->setVelocity(Vec2(-200, this->bodyPlayer->getVelocity().y));
}

void Player::moveToRight()
{
	this->bodyPlayer->setVelocity(Vec2(200, this->bodyPlayer->getVelocity().y));
}

void Player::resetVelocity()
{
	this->bodyPlayer->setVelocity(Vec2(this->bodyPlayer->getVelocity().x, 0));
}

void Player::jump()
{
	this->bodyPlayer->setVelocity(Vec2(this->bodyPlayer->getVelocity().x, 500));
}