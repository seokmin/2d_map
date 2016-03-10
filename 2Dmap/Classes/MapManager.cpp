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
		auto& currentNearNodeMap = _mapsForNodesWithIndex[i]->nearNodesMap;
		if (currentNearNodeMap.find(DIRECTION_1) == currentNearNodeMap.end())//이미 값이 들어있지 않은 경우
			currentNearNodeMap[DIRECTION_1] = _mapsForNodesWithIndex[i - WORLD_MAP_SIZE_WIDTH - 1];
		if (currentNearNodeMap.find(DIRECTION_2) == currentNearNodeMap.end())
			currentNearNodeMap[DIRECTION_2] = _mapsForNodesWithIndex[i - WORLD_MAP_SIZE_WIDTH];
		if (currentNearNodeMap.find(DIRECTION_3) == currentNearNodeMap.end())
			currentNearNodeMap[DIRECTION_3] = _mapsForNodesWithIndex[i - WORLD_MAP_SIZE_WIDTH + 1];
		if (currentNearNodeMap.find(DIRECTION_4) == currentNearNodeMap.end())
			currentNearNodeMap[DIRECTION_4] = _mapsForNodesWithIndex[i - 1];
		if (currentNearNodeMap.find(DIRECTION_6) == currentNearNodeMap.end())
			currentNearNodeMap[DIRECTION_6] = _mapsForNodesWithIndex[i + 1];
		if (currentNearNodeMap.find(DIRECTION_7) == currentNearNodeMap.end())
			currentNearNodeMap[DIRECTION_7] = _mapsForNodesWithIndex[i + WORLD_MAP_SIZE_WIDTH - 1];
		if (currentNearNodeMap.find(DIRECTION_8) == currentNearNodeMap.end())
			currentNearNodeMap[DIRECTION_8] = _mapsForNodesWithIndex[i + WORLD_MAP_SIZE_WIDTH];
		if (currentNearNodeMap.find(DIRECTION_9) == currentNearNodeMap.end())
			currentNearNodeMap[DIRECTION_9] = _mapsForNodesWithIndex[i + WORLD_MAP_SIZE_WIDTH + 1];
		if (currentNearNodeMap.find(DIRECTION_N) == currentNearNodeMap.end())
			currentNearNodeMap[DIRECTION_N] = _mapsForNodesWithIndex[i];
	}

	/**
	반대편 posNum을 반환
	posNum : 해당 좌표
	direction : 해당 타일이 어느쪽 외곽선인지 입력
	*/
	auto getOppositeMap = [=](unsigned posNum, DirectionKind direction){
		//원래의 좌표
		unsigned x = posNum % WORLD_MAP_SIZE_WIDTH;
		unsigned y = (posNum / WORLD_MAP_SIZE_WIDTH) + 1;
		//반환할 좌표
		unsigned targetX = x, targetY = y;
		
		switch (direction)
		{
		//사방
		case DIRECTION_2:
			targetY += WORLD_MAP_SIZE_HEIGHT - 1;
			break;
		case DIRECTION_4:
			targetX += WORLD_MAP_SIZE_WIDTH - 1;
			break;
		case DIRECTION_6:
			targetX -= WORLD_MAP_SIZE_WIDTH - 1;
			break;
		case DIRECTION_8:
			targetY -= WORLD_MAP_SIZE_HEIGHT - 1;
			break;
		//대각선 방향
		case DIRECTION_1:
			targetX += WORLD_MAP_SIZE_WIDTH - 1;
			targetY += WORLD_MAP_SIZE_HEIGHT - 1;
			break;
		case DIRECTION_3:
			targetX -= WORLD_MAP_SIZE_WIDTH - 1;
			targetY += WORLD_MAP_SIZE_HEIGHT - 1;
			break;
		case DIRECTION_7:
			targetX += WORLD_MAP_SIZE_WIDTH - 1;
			targetY -= WORLD_MAP_SIZE_HEIGHT - 1;
			break;
		case DIRECTION_9:
			targetX -= WORLD_MAP_SIZE_WIDTH - 1;
			targetY -= WORLD_MAP_SIZE_HEIGHT - 1;
			break;

		default:
			log("getOppositeMap : 잘못된 방향을 입력했습니다.");
			Beep(1000, 1000);
			break;
		}

		return WORLD_MAP_SIZE_WIDTH*(targetY - 1) + targetX;

	};

	//외곽선을 순환시키기 위한 루프
	for (int i = 0; i < WORLD_MAP_SIZE_HEIGHT; ++i)
	{
		for (int j = 0; j < WORLD_MAP_SIZE_WIDTH; ++j)
		{
			int posNum = WORLD_MAP_SIZE_WIDTH*i + j;
			if (posNum % WORLD_MAP_SIZE_WIDTH == 0)//가장 왼쪽 줄이면
				_mapsForNodesWithIndex[posNum]->nearNodesMap[DIRECTION_4] = _mapsForNodesWithIndex[getOppositeMap(posNum,DIRECTION_4)];
			if ((posNum + 1) % WORLD_MAP_SIZE_WIDTH == 0)//가장 오른쪽 줄이면
				_mapsForNodesWithIndex[posNum]->nearNodesMap[DIRECTION_6] = _mapsForNodesWithIndex[getOppositeMap(posNum, DIRECTION_6)];
			if (posNum < WORLD_MAP_SIZE_WIDTH)//가장 아랫쪽 줄이면
				_mapsForNodesWithIndex[posNum]->nearNodesMap[DIRECTION_2] = _mapsForNodesWithIndex[getOppositeMap(posNum, DIRECTION_2)];
			if (posNum >= WORLD_MAP_SIZE_HEIGHT*WORLD_MAP_SIZE_WIDTH - WORLD_MAP_SIZE_WIDTH)//가장 윗쪽 줄이면
			
				_mapsForNodesWithIndex[posNum]->nearNodesMap[DIRECTION_8] = _mapsForNodesWithIndex[getOppositeMap(posNum, DIRECTION_8)];
		}
 	}
	for (int i = 0; i < WORLD_MAP_SIZE_HEIGHT; ++i)
	{
		for (int j = 0; j < WORLD_MAP_SIZE_WIDTH; ++j)
		{
			int posNum = WORLD_MAP_SIZE_WIDTH*i + j;
			if (posNum % WORLD_MAP_SIZE_WIDTH == 0)//가장 왼쪽 줄이면
			{
				_mapsForNodesWithIndex[posNum]->nearNodesMap[DIRECTION_1] = _mapsForNodesWithIndex[posNum]->nearNodesMap[DIRECTION_4]->nearNodesMap[DIRECTION_2];
				_mapsForNodesWithIndex[posNum]->nearNodesMap[DIRECTION_7] = _mapsForNodesWithIndex[posNum]->nearNodesMap[DIRECTION_4]->nearNodesMap[DIRECTION_8];
			}
			if ((posNum + 1) % WORLD_MAP_SIZE_WIDTH == 0)//가장 오른쪽 줄이면
			{

				_mapsForNodesWithIndex[posNum]->nearNodesMap[DIRECTION_3] = _mapsForNodesWithIndex[posNum]->nearNodesMap[DIRECTION_6]->nearNodesMap[DIRECTION_2];
				_mapsForNodesWithIndex[posNum]->nearNodesMap[DIRECTION_9] = _mapsForNodesWithIndex[posNum]->nearNodesMap[DIRECTION_6]->nearNodesMap[DIRECTION_8];
			}
			if (posNum < WORLD_MAP_SIZE_WIDTH)//가장 아랫쪽 줄이면
			{
				_mapsForNodesWithIndex[posNum]->nearNodesMap[DIRECTION_1] = _mapsForNodesWithIndex[posNum]->nearNodesMap[DIRECTION_2]->nearNodesMap[DIRECTION_4];
				_mapsForNodesWithIndex[posNum]->nearNodesMap[DIRECTION_3] = _mapsForNodesWithIndex[posNum]->nearNodesMap[DIRECTION_2]->nearNodesMap[DIRECTION_6];
			}
			if (posNum >= WORLD_MAP_SIZE_HEIGHT*WORLD_MAP_SIZE_WIDTH - WORLD_MAP_SIZE_WIDTH)//가장 윗쪽 줄이면
			{
				_mapsForNodesWithIndex[posNum]->nearNodesMap[DIRECTION_7] = _mapsForNodesWithIndex[posNum]->nearNodesMap[DIRECTION_8]->nearNodesMap[DIRECTION_4];
				_mapsForNodesWithIndex[posNum]->nearNodesMap[DIRECTION_9] = _mapsForNodesWithIndex[posNum]->nearNodesMap[DIRECTION_8]->nearNodesMap[DIRECTION_6];
			}
		}
	}
	//_tiledMap 초기화
	for (auto i = _mapsForNodesWithIndex.begin(); i != _mapsForNodesWithIndex.end(); ++i)
		i->second->_tiledMap = nullptr;
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
	_nineZones[DIRECTION_N]->_tiledMap->setPosition(ccp(0,0));
	reposition();

	_handle->setPosition(ccp(0,0/*SCREEN_PIXEL_WIDTH/2,SCREEN_PIXEL_HEIGHT/2*/));

	return _handle;
}



void MapManager::reload(DirectionKind newZoneDirection)
{
	NodeTileMap* newCenterZone = _nineZones[newZoneDirection];


	auto checkNullAndLoadMap = [=](DirectionKind direction){
		if(_nineZones[direction] != nullptr)
			TMXTiledMap::create(_nineZones[direction]->_mapFileName);
	};

	//생 노가다 코드..
	switch (newZoneDirection)
	{
	case DIRECTION_N:
		break;
	case DIRECTION_1:
		break;
	case DIRECTION_2:
		_handle->removeChild(_nineZones[DIRECTION_7]->_tiledMap);
		_handle->removeChild(_nineZones[DIRECTION_8]->_tiledMap);
		_handle->removeChild(_nineZones[DIRECTION_9]->_tiledMap);
		_nineZones.erase(DIRECTION_7);
		_nineZones.erase(DIRECTION_8);
		_nineZones.erase(DIRECTION_9);
		_nineZones[DIRECTION_7] = _nineZones[DIRECTION_4];
		_nineZones[DIRECTION_8] = _nineZones[DIRECTION_N];
		_nineZones[DIRECTION_9] = _nineZones[DIRECTION_6];
		_nineZones[DIRECTION_4] = _nineZones[DIRECTION_1];
		_nineZones[DIRECTION_N] = _nineZones[DIRECTION_2];
		_nineZones[DIRECTION_6] = _nineZones[DIRECTION_3];

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
		_nineZones.erase(DIRECTION_3);
		_nineZones.erase(DIRECTION_6);
		_nineZones.erase(DIRECTION_9);
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
		_nineZones.erase(DIRECTION_1);
		_nineZones.erase(DIRECTION_4);
		_nineZones.erase(DIRECTION_7);
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
		_handle->removeChild(_nineZones[DIRECTION_1]->_tiledMap);
		_handle->removeChild(_nineZones[DIRECTION_2]->_tiledMap);
		_handle->removeChild(_nineZones[DIRECTION_3]->_tiledMap);
		_nineZones.erase(DIRECTION_1);
		_nineZones.erase(DIRECTION_2);
		_nineZones.erase(DIRECTION_3);
		_nineZones[DIRECTION_1] = _nineZones[DIRECTION_4];
		_nineZones[DIRECTION_2] = _nineZones[DIRECTION_N];
		_nineZones[DIRECTION_3] = _nineZones[DIRECTION_6];
		_nineZones[DIRECTION_4] = _nineZones[DIRECTION_7];
		_nineZones[DIRECTION_N] = _nineZones[DIRECTION_8];
		_nineZones[DIRECTION_6] = _nineZones[DIRECTION_9];

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

bool MapManager::isLoading()
{
// 	for (auto i : _nineZones)
// 	{
// 		i.second->
// 	}
	return true;
}

void MapManager::moveNineMaps(Vec2 vec)
{
	for (auto i : _nineZones)
	{
		Vec2 currentPos = i.second->_tiledMap->getPosition();
		i.second->_tiledMap->setPosition(currentPos+vec);
	}
}
