#ifndef _BASE_SCENE_H_
#define _BASE_SCENE_H_

#include "cocos2d.h"
#include "VisibleRect.h"

USING_NS_CC;
using namespace std;

class BaseScene : public CCScene
{
public: 
	BaseScene(bool bPortrait = false);
	virtual void onEnter();

	virtual void runThisTest() = 0;

	// The CallBack for back to the main menu scene
	virtual void MainMenuCallback(CCObject* pSender);
};

typedef CCLayer* (*NEWTESTFUNC)();
#define TESTLAYER_CREATE_FUNC(className) \
	static CCLayer* create##className() \
{ return new className(); }

#define CF(className) create##className

#endif
