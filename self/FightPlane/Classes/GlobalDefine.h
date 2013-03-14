#ifndef __GLOBALDEFINE__
#define __GLOBALDEFINE__

#include "FightScene/FirstScene.h"


enum
{
	FIRST_SCENE = 0,
    TEST_TRANSITIONS,
    TEST_PROGRESS_ACTIONS,
    TEST_EFFECTS,
    TEST_EASE_ACTIONS,
    TEST_MOTION_STREAK,
    TEST_DRAW_PRIMITIVES,
    TEST_COCOSNODE,
    TEST_TOUCHES,
    TEST_MENU,
    TESTS_COUNT,    
};

const std::string g_aTestNames[TESTS_COUNT] = {
    "1",
    "2",
    "3",
    "4",
    "5",
    "6",
    "7",
    "8",
    "9",
};

#define LINE_SPACE 40

#endif
