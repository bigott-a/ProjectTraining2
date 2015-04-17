#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "cocos2d.h"

class						Player : public cocos2d::Layer
{
public:
	Player(cocos2d::Size visiblesize, cocos2d::Vec2 origin);
	virtual					~Player(void);
	virtual bool			init(void);

	void					update(void);
	cocos2d::Sprite			*spritePlayer;
	void					moveToLeft(void);
	void					moveToRight(void);
	void					resetVelocity(void);
	void					jump(void);

private:
	cocos2d::Size			myVisibleSize;
	cocos2d::Vec2			myOrigin;
	cocos2d::PhysicsBody	*bodyPlayer;

};

#endif