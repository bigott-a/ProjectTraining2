#include "Game.h"

USING_NS_CC;

Scene* Game::createScene()
{
	Scene *scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	Game *layer = Game::create();
	layer->setPhyWorld(scene->getPhysicsWorld());
	scene->addChild(layer);

	return scene;
}

void Game::setPhyWorld(cocos2d::PhysicsWorld* world)
{
	this->m_world = world;
	this->m_world->setGravity(Vec2(0.0f, -600.0f));
}

bool Game::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	this->projectiles = new CCArray();
	this->ennemies = new CCArray();
	this->platforms = new CCArray();
	
	// création sprite représentant le sol
	Sprite *floor = Sprite::create();
	floor->setPosition(Vec2(0, visibleSize.height / 4));
	floor->setTextureRect(Rect(-500.0f, -5.0f, 1000.0f, 10.0f));
	floor->setAnchorPoint(Vec2(0, 0));
	floor->setTag(tagItem::PLATFORM);
	// ajout à la scene
	this->addChild(floor);
	

	PhysicsBody *body = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 5);
	edgeNode = Node::create();
	edgeNode->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	edgeNode->setPhysicsBody(body);
	edgeNode->setTag(tagItem::WINDOW);
	this->addChild(edgeNode);


	// création du joueur
	this->myPlayer = new Player(visibleSize, origin);
	this->myPlayer->spritePlayer->setTag(tagItem::PLAYER);
	// ajout a la scene
	this->addChild(this->myPlayer->spritePlayer);

	// init des touches claviers
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
	CCRect playerRect = CCRectMake(this->myPlayer->spritePlayer->getPositionX() - (this->myPlayer->spritePlayer->getContentSize().width / 2)
		, this->myPlayer->spritePlayer->getPositionY() - (this->myPlayer->spritePlayer->getContentSize().height / 2)
		, this->myPlayer->spritePlayer->getContentSize().width
		, this->myPlayer->spritePlayer->getContentSize().height);
	CCObject* it = NULL;
	CCObject* jt = NULL;
	CCArray *projectileToDelete = new CCArray;
	CCArray *ennemieToDelete = new CCArray;
	
	CCARRAY_FOREACH(this->projectiles, it)
	{
		CCSprite *projectile = dynamic_cast<CCSprite*>(it);
		CCRect projectileRect = CCRectMake(projectile->getPosition().x - (projectile->getContentSize().width / 2)
			, projectile->getPosition().y - (projectile->getContentSize().height / 2)
			, projectile->getContentSize().width
			, projectile->getContentSize().height);

		if (projectile->getTag() == tagItem::PLAYER_PROJECTILE)
		{
			CCARRAY_FOREACH(this->ennemies, jt)
			{
				CCSprite *target = dynamic_cast<CCSprite*>(jt);
				CCRect targetRect = CCRectMake(target->getPosition().x - (target->getContentSize().width / 2)
					, target->getPosition().y - (target->getContentSize().height / 2)
					, target->getContentSize().width
					, target->getContentSize().height);
				if (projectileRect.intersectsRect(targetRect))
				{
					// a playerProjectille touch a ennemie
					// do smthg ... like kill the ennemie
					// delete projectille
					ennemieToDelete->addObject(target);
					projectileToDelete->addObject(projectile);
				}
			}
		}
		else if (projectile->getTag() == tagItem::ENNEMIES_PROJECTILE)
		{
			if (projectileRect.intersectsRect(playerRect))
			{
				// a ennemiesProjectille touch the player
				// do smthg ... like do damage to player
				// delete projectille
				projectileToDelete->addObject(projectile);
			}
		}

		CCARRAY_FOREACH(this->platforms, jt)
		{
			CCSprite *target = dynamic_cast<CCSprite*>(jt);
			CCRect targetRect = CCRectMake(target->getPosition().x - (target->getContentSize().width / 2)
				, target->getPosition().y - (target->getContentSize().height / 2)
				, target->getContentSize().width
				, target->getContentSize().height);

			if (projectileRect.intersectsRect(targetRect))
			{
				// a playerProjectille touch a platform
				// do smthg ... like del the projectille
				projectileToDelete->addObject(projectile);
			}
		}

		if (projectile->getPosition().x - (projectile->getContentSize().width / 2) < 0
			|| projectile->getPosition().x - (projectile->getContentSize().width / 2) > Director::getInstance()->getVisibleSize().width
			|| projectile->getPosition().y - (projectile->getContentSize().height / 2) < 0
			|| projectile->getPosition().y - (projectile->getContentSize().height / 2) > Director::getInstance()->getVisibleSize().height)
		{
			// projectile go out of the window
			// delete him
			projectileToDelete->addObject(projectile);
		}
	}

	if (projectileToDelete->count() > 0)
		CCARRAY_FOREACH(projectileToDelete, it)
		{
			CCSprite *target = dynamic_cast<CCSprite*>(jt);
			this->projectiles->removeObject(target);
			this->removeChild(target, true);
		}

	if (ennemieToDelete->count() > 0)
		CCARRAY_FOREACH(ennemieToDelete, it)
	{
		CCSprite *target = dynamic_cast<CCSprite*>(jt);
		this->ennemies->removeObject(target);
		this->removeChild(target, true);
	}

	CCARRAY_FOREACH(this->platforms, it)
	{
		CCSprite *platform = dynamic_cast<CCSprite*>(it);
		CCRect platformRect = CCRectMake(platform->getPosition().x - (platform->getContentSize().width / 2)
			, platform->getPosition().y - (platform->getContentSize().height / 2)
			, platform->getContentSize().width
			, platform->getContentSize().height);

		if (platformRect.intersectsRect(playerRect))
		{
			this->myPlayer->resetVelocity();
			if (this->keySpacePressed)
			{
				this->myPlayer->jump();
				this->keySpacePressed = false;
			}
		}
	}

	if (this->keyRightPressed && !this->keyLeftPressed)
		this->myPlayer->moveToRight();
	else if (!this->keyRightPressed && this->keyLeftPressed)
		this->myPlayer->moveToLeft();

	this->myPlayer->update();
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