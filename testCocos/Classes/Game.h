#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "Player.h"

enum tagItem
{
	WINDOW,
	PLAYER,
	PLAYER_PROJECTILE,
	ENNEMIE,
	ENNEMIES_PROJECTILE,
	PLATFORM
};

class						Game : public cocos2d::Layer
{
public:
	static					cocos2d::Scene* createScene();
	virtual bool			init(void);
	void					menuCloseCallback(cocos2d::Ref* pSender);
	CREATE_FUNC(Game);

	void					setPhyWorld(cocos2d::PhysicsWorld* world);
	void					update(float delta);
	void					onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void					onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	
private:
	cocos2d::PhysicsWorld	*m_world;
	Player					*myPlayer;
	cocos2d::Node			*edgeNode;

	cocos2d::CCArray		*projectiles;
	cocos2d::CCArray		*ennemies;
	cocos2d::CCArray		*platforms;

	bool					keyRightPressed;
	bool					keyLeftPressed;
	bool					keySpacePressed;
};



#endif