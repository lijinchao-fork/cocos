#include "cocos2d.h"
#include "CCEGLView.h"
#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "SokobanLayer.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

USING_NS_CC;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
SokobanLayer *g_layer;

void Win32SetKeyLayer(SokobanLayer *layer)
{
	g_layer = layer;
}

void Win32KeyHook( UINT message,WPARAM wParam, LPARAM lParam )
{
	CCLog("Win32KeyHook message %d wParam %d lParam %d", message, wParam, lParam);
	if (g_layer)
		g_layer->onWin32KeyEvent(message, wParam, lParam);
}
#endif

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
    SimpleAudioEngine::end();
}


bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());

	// 从view中注册消息回调
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	// 处理Windows按键
	CCEGLView::sharedOpenGLView()->setAccelerometerKeyHook(Win32KeyHook);
#endif

	
    // turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    CCScene *pScene = HelloWorld::scene();

    // run
    pDirector->runWithScene(pScene);
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->stopAnimation();

    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();

    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
