#ifndef __TESTSCENE_SCENE_H__
#define __TESTSCENE_SCENE_H__

#include "cocos2d.h"
#include "VisibleRect.h"

class TestScene : public cocos2d::CCScene
{
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  

	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	//static cocos2d::CCScene* scene();
	virtual void onEnter();

	virtual void MainMenuCallback(CCObject* pSender);

	// implement the "static node()" method manually
	CREATE_FUNC(TestScene);
};

#endif // __TESTSCENE_SCENE_H__
