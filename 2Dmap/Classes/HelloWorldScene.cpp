#include "pch.h"
#include "HelloWorldScene.h"
#include "SampleCharacter.h"
#include "definition.h"
USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    ////메인 부분

	
	_sampleCharacter = new SampleCharacter();
	_sampleCharacter->setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	this->addChild(_sampleCharacter,1);


	///////////////////


    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//Close 부분
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 2);

	TMXTiledMap* _tiledMap = TMXTiledMap::create("Map/testmap.tmx");
	
	this->addChild(_tiledMap,0);
	//Size testMapSize = testMap->getContentSize();
	//log("Content size: %f, %f", testMapSize.width, testMapSize.height);

	this->scheduleUpdate();
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void HelloWorld::setViewPointCenter(cocos2d::Point position)
{
	cocos2d::Size winSize = cocos2d::Director::sharedDirector()->getWinSize();
	int x = MAX(position.x, winSize.width);
	int y = MAX(position.y, winSize.height);
	//x = MIN(x, (_tiledMap->getMapSize().width * _tiledMap->getTileSize().width) - winSize.width / 2);
	//y = MIN(x, (_tiledMap->getMapSize().height * _tiledMap->getTileSize().height) - winSize.height / 2);
	cocos2d::Point actualPosition = ccp(x, y);
	cocos2d::Point centerOfView = ccp(winSize.width / 2, winSize.height / 2);
	cocos2d::Point viewPoint = ccpSub(centerOfView, actualPosition);
	this->setPosition(viewPoint);
}

void HelloWorld::update(float delta)
{
	this->setViewPointCenter(_sampleCharacter->getPosition());
}
