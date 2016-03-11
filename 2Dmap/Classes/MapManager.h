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
	"Map/16.tmx",
	"Map/17.tmx",
	"Map/18.tmx",
	"Map/19.tmx",
	"Map/20.tmx",
	"Map/21.tmx",
	"Map/22.tmx",
	"Map/23.tmx",
	"Map/24.tmx",
	"Map/25.tmx",
	"Map/26.tmx",
	"Map/27.tmx",
	"Map/28.tmx",
	"Map/29.tmx",
	"Map/30.tmx",
	"Map/31.tmx",
	"Map/32.tmx",
	"Map/33.tmx",
	"Map/34.tmx",
	"Map/35.tmx",
	"Map/36.tmx"
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
	"Map16",
	"Map17",
	"Map18",
	"Map19",
	"Map20",
	"Map21",
	"Map22",
	"Map23",
	"Map24",
	"Map25",
	"Map26",
	"Map27",
	"Map28",
	"Map29",
	"Map30",
	"Map31",
	"Map32",
	"Map33",
	"Map34",
	"Map35",
	"Map36"
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
	void	reload(DirectionKind newZoneDirection);
	Size	getSizeOfMapPixel();
	Vec2	getPositionOfCenterMap();
	void moveNineMaps(Vec2 vec);
	bool	isLoading();
private:
	MapManager();
	MapManager(const MapManager& other);
	static MapManager*						_instance;
	std::map<int, NodeTileMap*>				_mapsForNodesWithIndex;
	/**
		현재 메모리에 올라있는 9개의 칸
	*/
	std::map<DirectionKind, NodeTileMap*>	_nineZones;
	Node*									_handle = nullptr;
	void									reposition();
	bool									_isLoading = false;
	void									requestSetAnchorPoint(Node* node, Vec2 vec);
	void									requestSetPosition(Node* node, Vec2 vec);
};