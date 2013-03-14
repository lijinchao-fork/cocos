#include "MainScene.h"
#include "AppMacros.h"
#include "GlobalDefine.h"
#include "VisibleRect.h"
#include "BaseScene.h"
USING_NS_CC;

static CCPoint s_tCurPos = CCPointZero;

CCScene* MainScene::scene()
{
	CCLog("MainScene::scene()");
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    MainScene *layer = MainScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainScene::init()
{
	CCLog("MainScene::init()");
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
                                        menu_selector(MainScene::menuCloseCallback));

	CCPoint cpPoint1 = ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
		origin.y + pCloseItem->getContentSize().height/2);

	pCloseItem->setPosition(cpPoint1);

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
	CCLog("point: %d, %d", CCPointZero.x, CCPointZero.y);
    this->addChild(pMenu, 1);

	//´´½¨menu

	m_pItemMenu = CCMenu::create();
	for (int i=0; i<=TESTS_COUNT; i++)
	{
		CCLabelTTF *label = CCLabelTTF::create(g_aTestNames[i].c_str(), "Arial", 24);
		CCMenuItemLabel* pMenuItem = CCMenuItemLabel::create(label, this, menu_selector(MainScene::menuNewCallBack));

		m_pItemMenu->addChild(pMenuItem, i + 10000);
		pMenuItem->setPosition( ccp( VisibleRect::center().x, (VisibleRect::top().y - (i + 1) * LINE_SPACE) ));
	}
	
	m_pItemMenu->setContentSize(CCSizeMake(VisibleRect::getVisibleRect().size.width, (TESTS_COUNT + 1)*LINE_SPACE));
	m_pItemMenu->setPosition(s_tCurPos);
	this->addChild(m_pItemMenu);
	setTouchEnabled(true);


    return true;
}


void MainScene::menuCloseCallback(CCObject* pSender)
{
	CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}


static BaseScene* CreateTestScene(int nIdx)
{
	CCDirector::sharedDirector()->purgeCachedData();

	BaseScene* pScene = NULL;

	switch (nIdx)
	{
	case FIRST_SCENE:
		pScene = new FirstScene(); break;
	default:
		break;
	}
	return pScene;
}
void MainScene::menuNewCallBack(CCObject* pSender)
{

	CCMenuItem *pMenuItem = (CCMenuItem*)pSender;
	int nIndex = pMenuItem->getZOrder() - 10000;
	BaseScene* pScene = CreateTestScene(nIndex);
	if(pScene)
	{
		pScene->runThisTest();
		pScene->release();
	}

}


void MainScene::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
	CCSetIterator it = pTouches->begin();
	CCTouch* touch = (CCTouch*)(*it);

	m_tBeginPos = touch->getLocation();    
	CCLog("ccTouchesBegan %f ", m_tBeginPos.y);
}

void MainScene::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
	CCSetIterator it = pTouches->begin();
	CCTouch* touch = (CCTouch*)(*it);

	CCPoint touchLocation = touch->getLocation();    
	float nMoveY = touchLocation.y - m_tBeginPos.y;

	CCLog("nMoveY %f ", nMoveY);
	CCPoint curPos  = m_pItemMenu->getPosition();
	CCPoint nextPos = ccp(curPos.x, curPos.y + nMoveY);

	if (nextPos.y < 0.0f)
	{
		m_pItemMenu->setPosition(CCPointZero);
		return;
	}

	if (nextPos.y > ((TESTS_COUNT + 1)* LINE_SPACE - VisibleRect::getVisibleRect().size.height))
	{
		m_pItemMenu->setPosition(ccp(0, ((TESTS_COUNT + 1)* LINE_SPACE - VisibleRect::getVisibleRect().size.height)));
		return;
	}

	m_pItemMenu->setPosition(nextPos);
	m_tBeginPos = touchLocation;
	s_tCurPos   = nextPos;
}