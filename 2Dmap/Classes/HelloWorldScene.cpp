#include "pch.h"
#include "HelloWorldScene.h"
#include "SampleCharacter.h"
#include "NodeTileMap.h"
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

	//초기화
	for (auto i = _isKeyPressed; i < _isKeyPressed + sizeof(_isKeyPressed) / sizeof(bool);++i)
		*i = false;

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

	for (int i = DIRECTION_1; i <= DIRECTION_9;++i)
	{
		_tiledMap.pushBack(TMXTiledMap::create("Map/testmap.tmx"));
		_tiledMap.at(i)->setAnchorPoint(ccp(0.5, 0.5));
		this->addChild(_tiledMap.at(i), 0);
	}
	{
		auto centerPos = ccp(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
		_sizeOfMap = _tiledMap.at(DIRECTION_N)->getContentSize();
		_tiledMap.at(DIRECTION_N)->setPosition(centerPos);
		_tiledMap.at(DIRECTION_1)->setPosition(centerPos + ccp(-1 * _sizeOfMap.width, -1 * _sizeOfMap.height));
		_tiledMap.at(DIRECTION_2)->setPosition(centerPos + ccp(0, -1 * _sizeOfMap.height));
		_tiledMap.at(DIRECTION_3)->setPosition(centerPos + ccp(1 * _sizeOfMap.width, -1 * _sizeOfMap.height));
		_tiledMap.at(DIRECTION_4)->setPosition(centerPos + ccp(-1 * _sizeOfMap.width, 0));
		_tiledMap.at(DIRECTION_6)->setPosition(centerPos + ccp(1 * _sizeOfMap.width, 0));
		_tiledMap.at(DIRECTION_7)->setPosition(centerPos + ccp(-1 * _sizeOfMap.width, 1 * _sizeOfMap.height));
		_tiledMap.at(DIRECTION_8)->setPosition(centerPos + ccp(0, 1 * _sizeOfMap.height));
		_tiledMap.at(DIRECTION_9)->setPosition(centerPos + ccp(1 * _sizeOfMap.width, 1 * _sizeOfMap.height));
	}
	//log("Content size: %f, %f", testMapSize.width, testMapSize.height);

	//이벤트디스패쳐
	EventListenerKeyboard* keyListener = EventListenerKeyboard::create();
	keyListener->onKeyPressed = CC_CALLBACK_2(HelloWorld::keyDownDispatcher, this);
	keyListener->onKeyReleased = CC_CALLBACK_2(HelloWorld::keyReleaseDispatcher, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);

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

void HelloWorld::update(float delta)
{
	moveCharacter();
	//this->setViewPointCenter(_sampleCharacter->getPosition());
}

void HelloWorld::keyDownDispatcher(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{
	_isKeyPressed[(unsigned)keyCode] = true;
}

void HelloWorld::keyReleaseDispatcher(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{
	_isKeyPressed[(unsigned)keyCode] = false;
}

void HelloWorld::moveCharacter()
{
	defineCharacterDirection();

	for (auto i : _tiledMap)
	{
		static float speed = 3.0f;
		if (_isKeyPressed[(unsigned)cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW])
			i->setPosition(i->getPosition() + ccp(+speed, 0));
		if (_isKeyPressed[(unsigned)cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW])
			i->setPosition(i->getPosition() + ccp(-speed, 0));
		if (_isKeyPressed[(unsigned)cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW])
			i->setPosition(i->getPosition() + ccp(0, -speed));
		if (_isKeyPressed[(unsigned)cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW])
			i->setPosition(i->getPosition() + ccp(0, speed));
	}
}

void HelloWorld::defineCharacterDirection()
{
}

void HelloWorld::mapLoader()
{
	Size mapSize = _tiledMap.at(DIRECTION_N)->getContentSize();

}

void HelloWorld::initializeMap()
{
	
}
