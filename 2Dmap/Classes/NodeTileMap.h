#pragma once
#include "definition.h"

class NodeTileMap
{
public:
	NodeTileMap(const std::string mapName,const std::string mapFilename);
	~NodeTileMap();
	std::string _mapName;
	std::string _mapFileName;
	cocos2d::TMXTiledMap* _tiledMap;
	std::map<DirectionKind, NodeTileMap*> nearNodesMap;
};