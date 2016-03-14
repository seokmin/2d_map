#pragma once
USING_NS_CC;

class MultiThreadedTiledMap :
	public TMXTiledMap
{
public:
	MultiThreadedTiledMap();
	~MultiThreadedTiledMap();
	CREATE_FUNC(MultiThreadedTiledMap);
};