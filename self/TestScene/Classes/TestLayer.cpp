
#include "TestLayer.h"
#include "AppMacros.h"
USING_NS_CC;


// on "init" you need to initialize your instance
bool TestLayer::init()
{
	CCLog("bool TestLayer::init()");
	//////////////////////////////
	if ( !CCLayer::init() )
	{
		return false;
	}

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	// back
	CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
		"back.png",
		"back.png",
		this,
		menu_selector(TestLayer::menuBackCallback));

	CCPoint cpPoint1 = ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
		origin.y + pCloseItem->getContentSize().height/2);

	CCLog("point: %d, %d", visibleSize.width, visibleSize.height);
	CCLog("point: %d, %d", cpPoint1.x, cpPoint1.y);
	pCloseItem->setPosition(cpPoint1);

	// create menu, it's an autorelease object
	CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
	pMenu->setPosition(CCPointZero);
	CCLog("point: %d, %d", CCPointZero.x, CCPointZero.y);
	this->addChild(pMenu, 1);

	return true;
}

void TestLayer::menuBackCallback(CCObject* pSender)
{
	CCDirector::sharedDirector()->popScene();
}