#include "FirstScene.h"
#include "../VisibleRect.h"

void FirstScene::runThisTest()
{
	CCLabelTTF* pLabel = CCLabelTTF::create("this is First Scene", "Arial", 20);
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	// position the label on the center of the screen
	pLabel->setPosition(ccp(VisibleRect::left().x + visibleSize.width / 2,
		VisibleRect::top().y - pLabel->getContentSize().height / 2));

	// add the label as a child to this layer
	this->addChild(pLabel, 1);

	CCDirector::sharedDirector()->replaceScene(this);
}
