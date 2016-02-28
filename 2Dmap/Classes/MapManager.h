#pragma once
#include "definition.h"
USING_NS_CC;

/*class HandleMap;*/

//1이 가장 좌측 하단
static const std::string WORLD_MAP_FILENAMES[WORLD_MAP_SIZE_WIDTH*WORLD_MAP_SIZE_HEIGHT] = {
	"Map/1.tmx",
	"Map/2.tmx",
	"Map/3.tmx",
	"Map/4.tmx",
	"Map/5.tmx",
	"Map/6.tmx",
	"Map/7.tmx",
	"Map/8.tmx",
	"Map/9.tmx",
	"Map/10.tmx",
	"Map/11.tmx",
	"Map/12.tmx",
	"Map/13.tmx",
	"Map/14.tmx",
	"Map/15.tmx",
	"Map/16.tmx"
};
static const std::string WORLD_MAP_NAMES[WORLD_MAP_SIZE_WIDTH*WORLD_MAP_SIZE_HEIGHT] = {
	"Map1",
	"Map2",
	"Map3",
	"Map4",
	"Map5",
	"Map6",
	"Map7",
	"Map8",
	"Map9",
	"Map10",
	"Map11",
	"Map12",
	"Map13",
	"Map14",
	"Map15",
	"Map16"
};

class NodeTileMap;

class MapManager
{

public:

	static MapManager* getInstance()
	{
		if (_instance == nullptr)
			_instance = new MapManager();
		return _instance;
	}
	void	initialize();
	void	loadZoneByName(const std::string zoneName);
	Node*	loadZoneByNumber(const int zoneNumber);
	void reload(DirectionKind newZoneDirection);

private:
	MapManager();
	MapManager(const MapManager& other);
	static MapManager*						_instance;
	std::map<int, NodeTileMap*>				_mapsForNodesWithIndex;
	std::map<DirectionKind, NodeTileMap*>	_nineZones;
	Node*									_handle = nullptr;
	void									reposition();
};