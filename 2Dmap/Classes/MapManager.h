#pragma once
#include "definition.h"
USING_NS_CC;

/*class HandleMap;*/

//1�� ���� ���� �ϴ�
static const std::string WORLD_MAP_FILENAMES[WORLD_MAP_SIZE_WIDTH*WORLD_MAP_SIZE_HEIGHT] = {
// 	"Map/1.tmx",
// 	"Map/2.tmx",
// 	"Map/3.tmx",
// 	"Map/4.tmx",
// 	"Map/5.tmx",
// 	"Map/6.tmx",
// 	"Map/7.tmx",
// 	"Map/8.tmx",
// 	"Map/9.tmx",
// 	"Map/10.tmx",
// 	"Map/11.tmx",
// 	"Map/12.tmx",
// 	"Map/13.tmx",
// 	"Map/14.tmx",
// 	"Map/15.tmx",
// 	"Map/16.tmx",
// 	"Map/17.tmx",
// 	"Map/18.tmx",
// 	"Map/19.tmx",
// 	"Map/20.tmx",
// 	"Map/21.tmx",
// 	"Map/22.tmx",
// 	"Map/23.tmx",
// 	"Map/24.tmx",
// 	"Map/25.tmx",
// 	"Map/26.tmx",
// 	"Map/27.tmx",
// 	"Map/28.tmx",
// 	"Map/29.tmx",
// 	"Map/30.tmx",
// 	"Map/31.tmx",
// 	"Map/32.tmx",
// 	"Map/33.tmx",
// 	"Map/34.tmx",
// 	"Map/35.tmx",
// 	"Map/36.tmx"
	"Map/small/001.tmx",
	"Map/small/002.tmx",
	"Map/small/003.tmx",
	"Map/small/004.tmx",
	"Map/small/005.tmx",
	"Map/small/006.tmx",
	"Map/small/007.tmx",
	"Map/small/008.tmx",
	"Map/small/009.tmx",
	"Map/small/010.tmx",
	"Map/small/011.tmx",
	"Map/small/012.tmx",
	"Map/small/013.tmx",
	"Map/small/014.tmx",
	"Map/small/015.tmx",
	"Map/small/016.tmx",
	"Map/small/017.tmx",
	"Map/small/018.tmx",
	"Map/small/019.tmx",
	"Map/small/020.tmx",
	"Map/small/021.tmx",
	"Map/small/022.tmx",
	"Map/small/023.tmx",
	"Map/small/024.tmx",
	"Map/small/025.tmx",
	"Map/small/026.tmx",
	"Map/small/027.tmx",
	"Map/small/028.tmx",
	"Map/small/029.tmx",
	"Map/small/030.tmx",
	"Map/small/031.tmx",
	"Map/small/032.tmx",
	"Map/small/033.tmx",
	"Map/small/034.tmx",
	"Map/small/035.tmx",
	"Map/small/036.tmx"
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

	static MapManager* getInstance(){if (_instance == nullptr)_instance = new MapManager();	return _instance;}

	/**
		���ϸ��� �ҷ��ͼ� �������� �а� �׷����� �����Ѵ�.
	*/
	void									initialize();

	/**
		zone ��ȣ�� ������� ���� �ε�
	*/
	Node*									loadZoneByNumber(const int zoneNumber);
	
	/**
		�̹� ȭ�鿡 ���ִ� ���¿��� ���� ��ũ���ϰ� ���� �� ���.
		newZoneDirection : ���� ���� ��ũ���ϰ��� �ϴ� ����
	*/
	void									reload(DirectionKind newZoneDirection);
	
	/**
		zone �ϳ��� ũ��(�ȼ�)�� ��ȯ
	*/
	Size									getSizeOfZoneInPixel();
	
	/**
		��� ���� ��� ��ǥ�� �������� position�� ��ȯ
	*/
	Vec2							getPosition();

	/**
		���� ȭ��� ��ǥ�� vec��ŭ �̵�
	*/
	void									moveMapPosition(Vec2 vec);

private:
	MapManager();
	MapManager(const MapManager& other);
	static MapManager*						_instance;
	std::map<int, NodeTileMap*>				_mapsForNodesWithIndex;

	/**
		���� �޸𸮿� �ö��ִ� 9���� ĭ
	*/
	std::map<DirectionKind, NodeTileMap*>	_nineZones;

	/**
		����ڰ� addchild�ϱ� ���� �ڵ�
	*/
	Node*									_handle = nullptr;

	/**
		��� ĭ�� �߽����� ���� �����Ѵ�.
	*/
	void									reposition();

	/**
		�ݴ��� posNum�� ��ȯ
		posNum : �ش� ��ǥ
		direction : �ش� Ÿ���� ����� �ܰ������� �Է�
	*/
	unsigned								getOppositeZoneNumber(unsigned posNum, DirectionKind direction);
};