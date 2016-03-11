#include "pch.h"
#include "NodeTileMap.h"

NodeTileMap::NodeTileMap(const std::string mapName, const std::string mapFilename)
{
	_mapName = mapName;
	_mapFileName = mapFilename;
}


NodeTileMap::~NodeTileMap()
{
}

void NodeTileMap::requestLoadMapFile(const std::string mapFileName, Node* handleToAdd)
{
	cocos2d::Director::getInstance()->getScheduler()->performFunctionInCocosThread([=]()
	{
		_tiledMap = cocos2d::TMXTiledMap::create(mapFileName);
		handleToAdd->addChild(_tiledMap);
	});
}