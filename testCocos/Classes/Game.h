#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "Player.h"

class				Game : public cocos2d::Layer
{
public:
	static			cocos2d::Scene* createScene();
	virtual bool	init(void);
	void			menuCloseCallback(cocos2d::Ref* pSender);
	CREATE_FUNC(Game);

	void			update(float delta);
	void			onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void			onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
private:
	Player			*myPlayer;
	bool			keyRightPressed;
	bool			keyLeftPressed;
	bool			keySpacePressed;
};

#endif