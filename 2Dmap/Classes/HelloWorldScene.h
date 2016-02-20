#pragma once

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
	//TMXTiledMap*		_tiledMap;
	SampleCharacter*	_sampleCharacter;
	void				update(float delta);
};