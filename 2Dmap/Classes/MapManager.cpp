#include "pch.h"
#include "MapManager.h"
#include "NodeTileMap.h"
/*#include "HandleMap.h"*/

MapManager* MapManager::_instance = nullptr;

MapManager::MapManager()
{
	/*_handle = dynamic_cast<HandleMap*>(HandleMap::create());*/
	_handle = Node::create();
}

MapManager::MapManager(const MapManager& other)
{

}


void MapManager::loadZoneByName(const std::string zoneName)
{

}

void MapManager::initialize()
{
	//일단 파일명 로딩
	for (int i = 0; i < WORLD_MAP_SIZE_HEIGHT; ++i)
	{
		for (int j = 0; j < WORLD_MAP_SIZE_WIDTH; ++j)
		{
			int posNum = WORLD_MAP_SIZE_WIDTH*i + j;
			_mapsForNodesWithIndex[posNum] = new NodeTileMap(WORLD_MAP_NAMES[posNum], WORLD_MAP_FILENAMES[posNum]);
		}
	}
	//외곽선을 nullptr로 채우기 위한 루프
	for (int i = 0; i < WORLD_MAP_SIZE_HEIGHT; ++i)
	{
		for (int j = 0; j < WORLD_MAP_SIZE_WIDTH; ++j)
		{
			int posNum = WORLD_MAP_SIZE_WIDTH*i + j;
			if (posNum % WORLD_MAP_SIZE_WIDTH == 0)//가장 왼쪽 줄이면
			{
				_mapsForNodesWithIndex[posNum]->nearNodesMap[DIRECTION_1] = nullptr;
				_mapsForNodesWithIndex[posNum]->nearNodesMap[DIRECTION_4] = nullptr;
				_mapsForNodesWithIndex[posNum]->nearNodesMap[DIRECTION_7] = nullptr;
			}
			if ((posNum + 1) % WORLD_MAP_SIZE_WIDTH == 0)//가장 오른쪽 줄이면
			{
				_mapsForNodesWithIndex[posNum]->nearNodesMap[DIRECTION_3] = nullptr;
				_mapsForNodesWithIndex[posNum]->nearNodesMap[DIRECTION_6] = nullptr;
				_mapsForNodesWithIndex[posNum]->nearNodesMap[DIRECTION_9] = nullptr;
			}
			if (posNum < WORLD_MAP_SIZE_WIDTH)//가장 아랫쪽 줄이면
			{
				_mapsForNodesWithIndex[posNum]->nearNodesMap[DIRECTION_1] = nullptr;
				_mapsForNodesWithIndex[posNum]->nearNodesMap[DIRECTION_2] = nullptr;
				_mapsForNodesWithIndex[posNum]->nearNodesMap[DIRECTION_3] = nullptr;
			}
			if (posNum >= WORLD_MAP_SIZE_HEIGHT*WORLD_MAP_SIZE_WIDTH-WORLD_MAP_SIZE_WIDTH)//가장 윗쪽 줄이면
			{
				_mapsForNodesWithIndex[posNum]->nearNodesMap[DIRECTION_7] = nullptr;
				_mapsForNodesWithIndex[posNum]->nearNodesMap[DIRECTION_8] = nullptr;
				_mapsForNodesWithIndex[posNum]->nearNodesMap[DIRECTION_9] = nullptr;
			}
		}
	}
	//그래프를 그려보자.
	for (unsigned i = 0; i < WORLD_MAP_SIZE_WIDTH*WORLD_MAP_SIZE_HEIGHT; ++i)
	{
		auto& nearNdMap = _mapsForNodesWithIndex[i]->nearNodesMap;
		if (nearNdMap.find(DIRECTION_1) == nearNdMap.end())//이미 값이 들어있지 않은 경우
			nearNdMap[DIRECTION_1] = _mapsForNodesWithIndex[i - WORLD_MAP_SIZE_WIDTH-1];
		if (nearNdMap.find(DIRECTION_2) == nearNdMap.end())
			nearNdMap[DIRECTION_2] = _mapsForNodesWithIndex[i - WORLD_MAP_SIZE_WIDTH];
		if (nearNdMap.find(DIRECTION_3) == nearNdMap.end())
			nearNdMap[DIRECTION_3] = _mapsForNodesWithIndex[i - WORLD_MAP_SIZE_WIDTH+1];
		if (nearNdMap.find(DIRECTION_4) == nearNdMap.end())
			nearNdMap[DIRECTION_4] = _mapsForNodesWithIndex[i-1];
		if (nearNdMap.find(DIRECTION_6) == nearNdMap.end())
			nearNdMap[DIRECTION_6] = _mapsForNodesWithIndex[i +1];
		if (nearNdMap.find(DIRECTION_7) == nearNdMap.end())
			nearNdMap[DIRECTION_7] = _mapsForNodesWithIndex[i + WORLD_MAP_SIZE_WIDTH-1];
		if (nearNdMap.find(DIRECTION_8) == nearNdMap.end())
			nearNdMap[DIRECTION_8] = _mapsForNodesWithIndex[i + WORLD_MAP_SIZE_WIDTH];
		if (nearNdMap.find(DIRECTION_9) == nearNdMap.end())
			nearNdMap[DIRECTION_9] = _mapsForNodesWithIndex[i + WORLD_MAP_SIZE_WIDTH+1];
		if (nearNdMap.find(DIRECTION_N) == nearNdMap.end())
			nearNdMap[DIRECTION_N] = _mapsForNodesWithIndex[i];
	}
}

Node* MapManager::loadZoneByNumber(const int zoneNumber)
{
	for (auto i = (int)DIRECTION_1; i <= (int)DIRECTION_9; ++i)
	{
		auto& currentZone = _nineZones[(DirectionKind)i];
		currentZone = _mapsForNodesWithIndex[zoneNumber];
		currentZone->_tiledMap = TMXTiledMap::create(_nineZones[(DirectionKind)i]->_mapFileName);
		_handle->addChild(currentZone->_tiledMap);
	}
	return _handle;
}