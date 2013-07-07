#ifndef __SOKOBAN_SCENE_H__
#define __SOKOBAN_SCENE_H__

#include "cocos2d.h"

class SokobanLayer : public cocos2d::CCLayer
{

public:

	// implement the "static node()" method manually
	CREATE_FUNC(SokobanLayer);

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();
	void drawSokoban();
	void drawIcon(int x, int y, cocos2d::CCRect &offset);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	// ´¦ÀíWindows°´¼ü
	void onWin32KeyEvent(UINT message,WPARAM wParam, LPARAM lParam);
#endif

	void move(char);

	int to_offset(char d, int width);

	void to_box(int index);
	void to_man(int index);
	void to_floor(int index);


	char m_Data[10000];

private:
	cocos2d::CCTexture2D* m_Icon;
	
	int m_w;
	int m_h;
	int m_man;

};

#endif //__SOKOBAN_SCENE_H__