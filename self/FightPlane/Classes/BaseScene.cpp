#include "BaseScene.h"
#include "MainScene.h"

BaseScene::BaseScene(bool bPortrait)
{

	CCScene::init();
}

void BaseScene::onEnter()
{
	CCScene::onEnter();

	//add the menu item for back to main menu
	//#if (CC_TARGET_PLATFORM == CC_PLATFORM_MARMALADE)
	//    CCLabelBMFont* label = CCLabelBMFont::create("MainMenu",  "fonts/arial16.fnt");
	//#else
	CCLabelTTF* label = CCLabelTTF::create("MainMenu", "Arial", 20);
	//#endif
	CCMenuItemLabel* pMenuItem = CCMenuItemLabel::create(label, this, menu_selector(BaseScene::MainMenuCallback));

	CCMenu* pMenu =CCMenu::create(pMenuItem, NULL);

	pMenu->setPosition( CCPointZero );
	pMenuItem->setPosition( ccp( VisibleRect::right().x - 50, VisibleRect::bottom().y + 25) );

	addChild(pMenu, 1);
}

void BaseScene::MainMenuCallback(CCObject* pSender)
{
	CCScene *pScene = MainScene::scene();

	CCDirector::sharedDirector()->replaceScene(pScene);
}
