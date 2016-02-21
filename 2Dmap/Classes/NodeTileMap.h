#pragma once
class NodeTileMap
{
public:
	NodeTileMap();
	~NodeTileMap();
	cocos2d::TMXTiledMap* _tiledMap;

	//cocos2d::Vector<NodeTileMap*>	nearNodes;
};