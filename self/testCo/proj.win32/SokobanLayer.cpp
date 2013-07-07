#include "SokobanLayer.h"
#include <string.h>
#include "AppDelegate.h"
using namespace cocos2d;

// on "init" you need to initialize your instance
bool SokobanLayer::init()
{
	bool bRet = false;
	do 
	{

		CC_BREAK_IF(! CCLayer::init());

		// 箱子相关
		m_Icon = CCTextureCache::sharedTextureCache()->addImage("borgar.png");
		char* data = "----#####--------------#---#--------------#$--#------------###--$##-----------#--$-$-#---------###-#-##-#---#######---#-##-#####--..##-$--$----------..######-###-#@##--..#----#-----#########----#######--------";
		strcpy_s(m_Data, data);
		m_w = 19;
		m_h = 11;

		m_man = 163;
		drawSokoban();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		extern void Win32SetKeyLayer(SokobanLayer *skbLayer);
		Win32SetKeyLayer(this);        // add layer as a child to scene
#endif

		bRet = true;
	} while (0);
	return bRet;
}

void SokobanLayer::drawSokoban()
{
	this->removeAllChildren();

	int IconWidth = 20;
	int IconHeight = 20;
	CCRect IconFloor(0,0,IconWidth,IconHeight);
	CCRect IconMan(IconWidth,0,IconWidth,IconHeight);
	CCRect IconBox(IconWidth*2,0,IconWidth,IconHeight);
	CCRect IconBoxDest(IconWidth*2,IconHeight,IconWidth,IconHeight);
	CCRect IconDest(0,IconHeight,IconWidth,IconHeight);
	CCRect IconManDest(IconWidth,IconHeight,IconWidth,IconHeight);
	CCRect IconWall(0,IconHeight*2,IconWidth,IconHeight);

	for(int i=0; i<m_w;i++){
		for(int j=0; j<m_h;j++){
			if(m_Data[j*m_w + i] == '#')//强
				drawIcon(i*IconWidth, j*IconHeight, IconWall);
			else if(m_Data[j*m_w + i] == '-')//空地
				drawIcon(i*IconWidth, j*IconHeight, IconFloor);
			else if(m_Data[j*m_w + i] == '@')//人
				drawIcon(i*IconWidth, j*IconHeight, IconMan);
			else if(m_Data[j*m_w + i] == '$')//#箱子
				drawIcon(i*IconWidth, j*IconHeight, IconBox);
			else if(m_Data[j*m_w + i] == '.')//目的地
				drawIcon(i*IconWidth, j*IconHeight, IconDest);
			else if(m_Data[j*m_w + i] == '+')//人在目的地
				drawIcon(i*IconWidth, j*IconHeight, IconManDest);
			else if(m_Data[j*m_w + i] == '*')//#成功态
				drawIcon(i*IconWidth, j*IconHeight, IconBoxDest);
		}
	}

}

void SokobanLayer::drawIcon(int x, int y, CCRect &offset)
{
	CCPoint pos(x, CCDirector::sharedDirector()->getWinSize().height - y);
	CCSprite* sprite = CCSprite::createWithTexture(m_Icon, offset);
	sprite->setPosition(pos);
	this->addChild(sprite, 0);
}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
// 处理Windows按键
void SokobanLayer::onWin32KeyEvent(UINT message,WPARAM wParam, LPARAM lParam )
{
    CCLog("onWin32KeyEvent message %d wParam %d lParam %d", message, wParam, lParam);
    /*
    // Up
    Win32KeyHook message 256 wParam 38 lParam 21495809
    onWin32KeyEvent message 256 wParam 38 lParam 21495809
    Win32KeyHook message 257 wParam 38 lParam -1052246015
    onWin32KeyEvent message 257 wParam 38 lParam -1052246015
    // Down
    Win32KeyHook message 256 wParam 40 lParam 22020097
    onWin32KeyEvent message 256 wParam 40 lParam 22020097
    Win32KeyHook message 257 wParam 40 lParam -1051721727
    onWin32KeyEvent message 257 wParam 40 lParam -1051721727
    // Left
    Win32KeyHook message 256 wParam 37 lParam 21692417
    onWin32KeyEvent message 256 wParam 37 lParam 21692417
    Win32KeyHook message 257 wParam 37 lParam -1052049407
    onWin32KeyEvent message 257 wParam 37 lParam -1052049407
    // Right
    Win32KeyHook message 256 wParam 39 lParam 21823489
    onWin32KeyEvent message 256 wParam 39 lParam 21823489
    Win32KeyHook message 257 wParam 39 lParam -1051918335
    onWin32KeyEvent message 257 wParam 39 lParam -1051918335
    */
    if (message == 256)
    {
        switch (wParam)
        {
        case 38:
			move('u');
			drawSokoban();
            break;
        case 40:
			move('d');
			drawSokoban();
            break;
        case 37:
			move('l');
			drawSokoban();
            break;
        case 39:
			move('r');
			drawSokoban();
            break;
        }
    }
    else if (message == 257)
    {
    }
}
#endif



void SokobanLayer::to_box(int index)
{
	if(m_Data[index] == '-' || m_Data[index] == '@')
		m_Data[index] = '$';
	else
		m_Data[index] = '*';
}


void SokobanLayer::to_man(int index)
{
	if(m_Data[index] == '-' || m_Data[index] == '$')
		m_Data[index] = '@';
	else
		m_Data[index] = '+';
}

void SokobanLayer::to_floor(int index)
{
	if(m_Data[index] == '@' || m_Data[index] == '$')
		m_Data[index] = '-';
	else
		m_Data[index] = '.';
}



void SokobanLayer::move(char direct)
{
	int h = to_offset(direct, m_w);
	int h2 = 2 * h;
	if(m_Data[m_man + h] == '-' || m_Data[m_man + h] == '.')
	{
		to_man(m_man+h);
		to_floor(m_man);
		m_man += h;
	}
	else if((m_Data[m_man + h] == '*' || m_Data[m_man + h] == '$')&&(m_Data[m_man + h2] == '-' || m_Data[m_man + 2] == '.'))
	{
		to_box(m_man + h2);
		to_man(m_man + h);
		to_floor(m_man);
		m_man += h;
	}
}

int SokobanLayer::to_offset(char d, int width){
	switch(d){
	case 'l':
		return -1;
	case 'u':
		return -width;
	case 'r':
		return 1;
	case 'd':
		return width;
	}
}