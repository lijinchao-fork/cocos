
#include "TestScene.h"
#include "TestLayer.h"
#include "AppMacros.h"
USING_NS_CC;


// on "init" you need to initialize your instance
bool TestScene::init()
{
	CCScene::init();
	return true;
}


void TestScene::onEnter()
{
	CCScene::onEnter();

	//add the menu item for back to main menu
	//#if (CC_TARGET_PLATFORM == CC_PLATFORM_MARMALADE)
	//    CCLabelBMFont* label = CCLabelBMFont::create("MainMenu",  "fonts/arial16.fnt");
	//#else
	CCLabelTTF* label = CCLabelTTF::create("MainMenu", "Arial", 20);
	//#endif
	CCMenuItemLabel* pMenuItem = CCMenuItemLabel::create(label, this, menu_selector(TestScene::MainMenuCallback));

	CCMenu* pMenu =CCMenu::create(pMenuItem, NULL);

	pMenu->setPosition( CCPointZero );
	pMenuItem->setPosition( ccp( VisibleRect::right().x - 50, VisibleRect::bottom().y + 25) );

	addChild(pMenu, 1);
}

void TestScene::MainMenuCallback(CCObject* pSender)
{
	
	CCDirector::sharedDirector()->popScene();
}
