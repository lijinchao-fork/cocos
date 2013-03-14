#include "HelloWorldScene.h"
#include "TestScene.h"
#include "TestLayer.h"
#include "AppMacros.h"

USING_NS_CC;


CCScene* HelloWorld::scene()
{
	CCLog("HelloWorld::scene()");
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	CCLog("HelloWorld::init()");
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }

    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "unclicked.png",
                                        "selected.png",
                                        this,
                                        menu_selector(HelloWorld::menuCloseCallback));

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

	// add a "new" icon to new a scene. it's an autorelease object
	CCMenuItemImage *pNewItem = CCMenuItemImage::create(
		"new.png",
		"new.png",
		this,
		menu_selector(HelloWorld::menuNewCallBack));

	CCPoint cpPoint2 = ccp(origin.x + visibleSize.width / 2 - pCloseItem->getContentSize().width/2 ,
		origin.y + pCloseItem->getContentSize().height/2);

	pNewItem->setPosition(cpPoint2);

	// create menu, it's an autorelease object
	pMenu = CCMenu::create(pNewItem, NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu, 1);


	// add new scene
	CCLabelTTF* label = CCLabelTTF::create("NewScene", "Arial", 20);
	//#endif
	CCMenuItemLabel* pMenuItem = CCMenuItemLabel::create(label, this, menu_selector(HelloWorld::menuNewSceneCallback));

	CCMenu* pNewSceneMenu =CCMenu::create(pMenuItem, NULL);

	pNewSceneMenu->setPosition( CCPointZero );
	pNewSceneMenu->setPosition( ccp( VisibleRect::right().x - 150, VisibleRect::bottom().y + 25) );

	addChild(pNewSceneMenu, 1);
    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Arial", TITLE_FONT_SIZE);
    
    // position the label on the center of the screen
	pLabel->setPosition(ccp(origin.x + pLabel->getContentSize().width / 2,
		origin.y + visibleSize.height / 2 - pLabel->getContentSize().height / 2));

    // add the label as a child to this layer
    this->addChild(pLabel, 1);

    // add "HelloWorld" splash screen"
	CCSprite* pSprite = CCSprite::create("test.png");
    //CCSprite* pSprite = CCSprite::create("CloseSelected.png");

    // position the sprite on the center of the screen
    pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(pSprite, 0);
    
    return true;
}


void HelloWorld::menuCloseCallback(CCObject* pSender)
{
	CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void HelloWorld::menuNewCallBack(CCObject* pSender)
{
	CCScene *pScene = CCScene::create();

	CCLayer *pLayer = TestLayer::create();
	pScene->addChild(pLayer);
	// run
	CCDirector* pDirector = CCDirector::sharedDirector();
	//pDirector->replaceScene((CCScene*)pScene);
	pDirector->pushScene(pScene);
}

void HelloWorld::menuNewSceneCallback(CCObject* pSender)
{
	TestScene *pScene = TestScene::create();
	CCLayer *pLayer = CCLayer::create();
	pScene->addChild(pLayer);

	CCDirector::sharedDirector()->pushScene(pScene);
}