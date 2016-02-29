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
			if (posNum >= WORLD_MAP_SIZE_HEIGHT*WORLD_MAP_SIZE_WIDTH - WORLD_MAP_SIZE_WIDTH)//가장 윗쪽 줄이면
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
			nearNdMap[DIRECTION_1] = _mapsForNodesWithIndex[i - WORLD_MAP_SIZE_WIDTH - 1];
		if (nearNdMap.find(DIRECTION_2) == nearNdMap.end())
			nearNdMap[DIRECTION_2] = _mapsForNodesWithIndex[i - WORLD_MAP_SIZE_WIDTH];
		if (nearNdMap.find(DIRECTION_3) == nearNdMap.end())
			nearNdMap[DIRECTION_3] = _mapsForNodesWithIndex[i - WORLD_MAP_SIZE_WIDTH + 1];
		if (nearNdMap.find(DIRECTION_4) == nearNdMap.end())
			nearNdMap[DIRECTION_4] = _mapsForNodesWithIndex[i - 1];
		if (nearNdMap.find(DIRECTION_6) == nearNdMap.end())
			nearNdMap[DIRECTION_6] = _mapsForNodesWithIndex[i + 1];
		if (nearNdMap.find(DIRECTION_7) == nearNdMap.end())
			nearNdMap[DIRECTION_7] = _mapsForNodesWithIndex[i + WORLD_MAP_SIZE_WIDTH - 1];
		if (nearNdMap.find(DIRECTION_8) == nearNdMap.end())
			nearNdMap[DIRECTION_8] = _mapsForNodesWithIndex[i + WORLD_MAP_SIZE_WIDTH];
		if (nearNdMap.find(DIRECTION_9) == nearNdMap.end())
			nearNdMap[DIRECTION_9] = _mapsForNodesWithIndex[i + WORLD_MAP_SIZE_WIDTH + 1];
		if (nearNdMap.find(DIRECTION_N) == nearNdMap.end())
			nearNdMap[DIRECTION_N] = _mapsForNodesWithIndex[i];
	}
}

Node* MapManager::loadZoneByNumber(const int zoneNumber)
{
	//일단 반복문 없이 생짜로 때려박는다.
	NodeTileMap* centerZone = _mapsForNodesWithIndex[zoneNumber-1];
	_nineZones[DIRECTION_N] = centerZone;
	_nineZones[DIRECTION_1] = centerZone->nearNodesMap[DIRECTION_1];
	_nineZones[DIRECTION_2] = centerZone->nearNodesMap[DIRECTION_2];
	_nineZones[DIRECTION_3] = centerZone->nearNodesMap[DIRECTION_3];
	_nineZones[DIRECTION_4] = centerZone->nearNodesMap[DIRECTION_4];
	_nineZones[DIRECTION_6] = centerZone->nearNodesMap[DIRECTION_6];
	_nineZones[DIRECTION_7] = centerZone->nearNodesMap[DIRECTION_7];
	_nineZones[DIRECTION_8] = centerZone->nearNodesMap[DIRECTION_8];
	_nineZones[DIRECTION_9] = centerZone->nearNodesMap[DIRECTION_9];
	
	for (int i = (int)DIRECTION_1; i <= (int)DIRECTION_9; ++i)
	{
		_nineZones[(DirectionKind)i]->_tiledMap = TMXTiledMap::create(_nineZones[(DirectionKind)i]->_mapFileName);
		_handle->addChild(_nineZones[(DirectionKind)i]->_tiledMap);
	}

	for (int i = DIRECTION_1; i <= DIRECTION_9; ++i)
	{
		_nineZones[(DirectionKind)i]->_tiledMap->setAnchorPoint(ccp(0.5, 0.5));
	}

	reposition();

	return _handle;
}



void MapManager::reload(DirectionKind newZoneDirection)
{
	NodeTileMap* newCenterZone = _nineZones[newZoneDirection];

	//생 노가다 코드..
	switch (newZoneDirection)
	{
	case DIRECTION_N:
		break;
	case DIRECTION_1:
		break;
	case DIRECTION_2:
		_handle->removeChild(_nineZones[DIRECTION_1]->_tiledMap);
		_handle->removeChild(_nineZones[DIRECTION_2]->_tiledMap);
		_handle->removeChild(_nineZones[DIRECTION_3]->_tiledMap);
		delete _nineZones[DIRECTION_1];
		delete _nineZones[DIRECTION_2];
		delete _nineZones[DIRECTION_3];
		_nineZones[DIRECTION_1] = _nineZones[DIRECTION_4];
		_nineZones[DIRECTION_2] = _nineZones[DIRECTION_N];
		_nineZones[DIRECTION_3] = _nineZones[DIRECTION_6];
		_nineZones[DIRECTION_4] = _nineZones[DIRECTION_7];
		_nineZones[DIRECTION_N] = _nineZones[DIRECTION_8];
		_nineZones[DIRECTION_6] = _nineZones[DIRECTION_9];

		_nineZones[DIRECTION_1] = newCenterZone->nearNodesMap[DIRECTION_1];
		_nineZones[DIRECTION_2] = newCenterZone->nearNodesMap[DIRECTION_2];
		_nineZones[DIRECTION_3] = newCenterZone->nearNodesMap[DIRECTION_3];

		_nineZones[DIRECTION_1]->_tiledMap = TMXTiledMap::create(_nineZones[DIRECTION_1]->_mapFileName);
		_nineZones[DIRECTION_2]->_tiledMap = TMXTiledMap::create(_nineZones[DIRECTION_2]->_mapFileName);
		_nineZones[DIRECTION_3]->_tiledMap = TMXTiledMap::create(_nineZones[DIRECTION_3]->_mapFileName);
		_handle->addChild(_nineZones[DIRECTION_1]->_tiledMap);
		_handle->addChild(_nineZones[DIRECTION_2]->_tiledMap);
		_handle->addChild(_nineZones[DIRECTION_3]->_tiledMap);
		break;
	case DIRECTION_3:
		break;
	case DIRECTION_4:
		_handle->removeChild(_nineZones[DIRECTION_3]->_tiledMap);
		_handle->removeChild(_nineZones[DIRECTION_6]->_tiledMap);
		_handle->removeChild(_nineZones[DIRECTION_9]->_tiledMap);
		delete _nineZones[DIRECTION_3];
		delete _nineZones[DIRECTION_6];
		delete _nineZones[DIRECTION_9];
		_nineZones[DIRECTION_3] = _nineZones[DIRECTION_2];
		_nineZones[DIRECTION_6] = _nineZones[DIRECTION_N];
		_nineZones[DIRECTION_9] = _nineZones[DIRECTION_8];
		_nineZones[DIRECTION_2] = _nineZones[DIRECTION_1];
		_nineZones[DIRECTION_N] = _nineZones[DIRECTION_4];
		_nineZones[DIRECTION_8] = _nineZones[DIRECTION_7];

		_nineZones[DIRECTION_1] = newCenterZone->nearNodesMap[DIRECTION_1];
		_nineZones[DIRECTION_4] = newCenterZone->nearNodesMap[DIRECTION_4];
		_nineZones[DIRECTION_7] = newCenterZone->nearNodesMap[DIRECTION_7];

		_nineZones[DIRECTION_1]->_tiledMap = TMXTiledMap::create(_nineZones[DIRECTION_1]->_mapFileName);
		_nineZones[DIRECTION_4]->_tiledMap = TMXTiledMap::create(_nineZones[DIRECTION_4]->_mapFileName);
		_nineZones[DIRECTION_7]->_tiledMap = TMXTiledMap::create(_nineZones[DIRECTION_7]->_mapFileName);
		_handle->addChild(_nineZones[DIRECTION_1]->_tiledMap);
		_handle->addChild(_nineZones[DIRECTION_4]->_tiledMap);
		_handle->addChild(_nineZones[DIRECTION_7]->_tiledMap);
		break;
	case DIRECTION_6:
		_handle->removeChild(_nineZones[DIRECTION_1]->_tiledMap);
		_handle->removeChild(_nineZones[DIRECTION_4]->_tiledMap);
		_handle->removeChild(_nineZones[DIRECTION_7]->_tiledMap);
		delete _nineZones[DIRECTION_1];
		delete _nineZones[DIRECTION_4];
		delete _nineZones[DIRECTION_7];
		_nineZones[DIRECTION_1] = _nineZones[DIRECTION_2];
		_nineZones[DIRECTION_4] = _nineZones[DIRECTION_N];
		_nineZones[DIRECTION_7] = _nineZones[DIRECTION_8];
		_nineZones[DIRECTION_2] = _nineZones[DIRECTION_3];
		_nineZones[DIRECTION_N] = _nineZones[DIRECTION_6];
		_nineZones[DIRECTION_8] = _nineZones[DIRECTION_9];

		_nineZones[DIRECTION_3] = newCenterZone->nearNodesMap[DIRECTION_3];
		_nineZones[DIRECTION_6] = newCenterZone->nearNodesMap[DIRECTION_6];
		_nineZones[DIRECTION_9] = newCenterZone->nearNodesMap[DIRECTION_9];

		_nineZones[DIRECTION_3]->_tiledMap = TMXTiledMap::create(_nineZones[DIRECTION_3]->_mapFileName);
		_nineZones[DIRECTION_6]->_tiledMap = TMXTiledMap::create(_nineZones[DIRECTION_6]->_mapFileName);
		_nineZones[DIRECTION_9]->_tiledMap = TMXTiledMap::create(_nineZones[DIRECTION_9]->_mapFileName);
		_handle->addChild(_nineZones[DIRECTION_3]->_tiledMap);
		_handle->addChild(_nineZones[DIRECTION_6]->_tiledMap);
		_handle->addChild(_nineZones[DIRECTION_9]->_tiledMap);
		break;
	case DIRECTION_7:
		break;
	case DIRECTION_8:
		_handle->removeChild(_nineZones[DIRECTION_7]->_tiledMap);
		_handle->removeChild(_nineZones[DIRECTION_8]->_tiledMap);
		_handle->removeChild(_nineZones[DIRECTION_9]->_tiledMap);
		delete _nineZones[DIRECTION_7];
		delete _nineZones[DIRECTION_8];
		delete _nineZones[DIRECTION_9];
		_nineZones[DIRECTION_7] = _nineZones[DIRECTION_4];
		_nineZones[DIRECTION_8] = _nineZones[DIRECTION_N];
		_nineZones[DIRECTION_9] = _nineZones[DIRECTION_6];
		_nineZones[DIRECTION_4] = _nineZones[DIRECTION_1];
		_nineZones[DIRECTION_N] = _nineZones[DIRECTION_2];
		_nineZones[DIRECTION_6] = _nineZones[DIRECTION_3];

		_nineZones[DIRECTION_7] = newCenterZone->nearNodesMap[DIRECTION_7];
		_nineZones[DIRECTION_8] = newCenterZone->nearNodesMap[DIRECTION_8];
		_nineZones[DIRECTION_9] = newCenterZone->nearNodesMap[DIRECTION_9];

		_nineZones[DIRECTION_7]->_tiledMap = TMXTiledMap::create(_nineZones[DIRECTION_7]->_mapFileName);
		_nineZones[DIRECTION_8]->_tiledMap = TMXTiledMap::create(_nineZones[DIRECTION_8]->_mapFileName);
		_nineZones[DIRECTION_9]->_tiledMap = TMXTiledMap::create(_nineZones[DIRECTION_9]->_mapFileName);
		_handle->addChild(_nineZones[DIRECTION_7]->_tiledMap);
		_handle->addChild(_nineZones[DIRECTION_8]->_tiledMap);
		_handle->addChild(_nineZones[DIRECTION_9]->_tiledMap);
		break;
	case DIRECTION_9:
		break;
	}

	reposition();
}

/**
	가운데 칸을 중심으로 맵을 정렬한다.
*/
void MapManager::reposition()
{
	auto centerPos = _nineZones[DIRECTION_N]->_tiledMap->getPosition();
	Size sizeOfMap = _nineZones[DIRECTION_N]->_tiledMap->getContentSize();
	_nineZones[DIRECTION_N]->_tiledMap->setPosition(centerPos);
	_nineZones[DIRECTION_1]->_tiledMap->setPosition(centerPos + ccp(-1 * sizeOfMap.width, -1 * sizeOfMap.height));
	_nineZones[DIRECTION_2]->_tiledMap->setPosition(centerPos + ccp(0, -1 * sizeOfMap.height));
	_nineZones[DIRECTION_3]->_tiledMap->setPosition(centerPos + ccp(1 * sizeOfMap.width, -1 * sizeOfMap.height));
	_nineZones[DIRECTION_4]->_tiledMap->setPosition(centerPos + ccp(-1 * sizeOfMap.width, 0));
	_nineZones[DIRECTION_6]->_tiledMap->setPosition(centerPos + ccp(1 * sizeOfMap.width, 0));
	_nineZones[DIRECTION_7]->_tiledMap->setPosition(centerPos + ccp(-1 * sizeOfMap.width, 1 * sizeOfMap.height));
	_nineZones[DIRECTION_8]->_tiledMap->setPosition(centerPos + ccp(0, 1 * sizeOfMap.height));
	_nineZones[DIRECTION_9]->_tiledMap->setPosition(centerPos + ccp(1 * sizeOfMap.width, 1 * sizeOfMap.height));
	for (int i = DIRECTION_1; i <= DIRECTION_9; ++i)
	{
		_nineZones[(DirectionKind)i]->_tiledMap->setAnchorPoint(ccp(0.5, 0.5));
	}
}

Size MapManager::getSizeOfMapPixel()
{
	return _nineZones[DIRECTION_N]->_tiledMap->getContentSize();
}

cocos2d::Vec2 MapManager::getPositionOfCenterMap()
{
	return _nineZones[DIRECTION_N]->_tiledMap->getPosition();
}
