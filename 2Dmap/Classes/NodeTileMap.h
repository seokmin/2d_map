#pragma once
#include "definition.h"
USING_NS_CC;

class NodeTileMap
{
public:
	NodeTileMap(const std::string mapName,const std::string mapFilename);
	~NodeTileMap();
	std::string								_mapName;
	std::string								_mapFileName;
	cocos2d::TMXTiledMap*					_tiledMap;
	std::map<DirectionKind, NodeTileMap*>	nearNodesMap;
	bool									isLoading = false;
	void									requestLoadMapFile(const std::string mapFileName, Node* handleToAdd);
	void									requestLoadMapFile(Node* node, Vec2 vec);
};