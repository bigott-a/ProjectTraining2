#include "Game.h"

USING_NS_CC;

Scene* Game::createScene()
{
	Scene *scene = Scene::createWithPhysics();
	Game *layer = Game::create();

	scene->addChild(layer);

	return scene;
}

bool Game::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// création sprite représentant le sol
	Sprite *floor = Sprite::create();
	floor->setPosition(Vec2(0, visibleSize.height / 4));
	floor->setAnchorPoint(Vec2(0, 0));
	// création du collider pour le sol
	PhysicsBody *physicsFloor = PhysicsBody::createBox(Size(1000, 2), PhysicsMaterial(1.0f, 0.0f, 0.0f));
	physicsFloor->setDynamic(false);
	// set le collider au sprite
	floor->setPhysicsBody(physicsFloor);
	// ajout à la scene
	this->addChild(floor);

	// création du joueur
	this->myPlayer = new Player(visibleSize, origin);
	// ajout a la scene
	this->addChild(this->myPlayer->spritePlayer);

	this->keyRightPressed = false;
	this->keyLeftPressed = false;
	this->keySpacePressed = false;

	// set et ajout event keyboard
	EventListenerKeyboard *listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(Game::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(Game::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	// ajout de la fct update dans le runtime
	this->scheduleUpdate();

	return true;
}

void Game::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW :
		this->keyLeftPressed = true;
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW :
		this->keyRightPressed = true;
		break;
	case EventKeyboard::KeyCode::KEY_SPACE :
		this->keySpacePressed = true;
		break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		this->myPlayer->resetVelocity();
		break;
	default :
		log("Key with keycode %d pressed", keyCode);
		break;
	}
}

void Game::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW :
		this->keyLeftPressed = false;
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW :
		this->keyRightPressed = false;
		break;
	case EventKeyboard::KeyCode::KEY_SPACE :
		this->keySpacePressed = false;
		break;
	default :
		log("Key with keycode %d released", keyCode);
		break;
	}
}

void Game::update(float delta)
{
	this->myPlayer->update();
	if (this->keyRightPressed && !this->keyLeftPressed)
		this->myPlayer->moveToRight();
	else if (!this->keyRightPressed && this->keyLeftPressed)
		this->myPlayer->moveToLeft();
	if (this->keySpacePressed)
	{
		this->myPlayer->jump();
		this->keySpacePressed = false;
	}
}

void Game::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
	return;
#endif

	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}