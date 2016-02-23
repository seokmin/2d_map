#pragma once
#include "definition.h"
class SampleCharacter;

class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

	void setViewPointCenter(cocos2d::Point position);

private:
	SampleCharacter*				_sampleCharacter;
	void							update(float delta);
	void							keyDownDispatcher(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);
	void							keyReleaseDispatcher(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);
	bool							_isKeyPressed[166/*Å°Á¾·ù*/];
	void							moveCharacter();
	Node*							_handleForMap = nullptr;
};