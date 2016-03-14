#pragma once
#include "definition.h"
USING_NS_CC;


//1이 가장 좌측 하단
static const std::string WORLD_MAP_FILENAMES[WORLD_MAP_SIZE_WIDTH*WORLD_MAP_SIZE_HEIGHT] = {
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
	"Map1","Map2","Map3","Map4","Map5","Map6",
	"Map7",	"Map8",	"Map9",	"Map10","Map11","Map12",
	"Map13","Map14","Map15","Map16","Map17","Map18",
	"Map19","Map20","Map21","Map22","Map23","Map24",
	"Map25","Map26","Map27","Map28","Map29","Map30",
	"Map31","Map32","Map33","Map34","Map35","Map36"
};

class NodeTileMap;

class MapManager
{

public:

	static MapManager* getInstance(){if (_instance == nullptr)_instance = new MapManager();	return _instance;}

	/**
		파일명을 불러와서 맵파일을 읽고 그래프를 생성한다.
	*/
	void	initialize();

	/**
		zone 번호를 기반으로 맵을 로딩하고 handle을 반환
	*/
	Node*	loadZoneByNumber(const int zoneNumber);
	
	/**
		이미 화면에 떠있는 상태에서 맵을 스크롤하고 싶을 때 사용.
		newZoneDirection : 새로 맵을 스크롤하고자 하는 방향
	*/
	void	reload(DirectionKind newZoneDirection);
	
	/**
		zone 하나의 크기(픽셀)를 반환
	*/
	Size	getSizeOfZoneInPixel();
	
	/**
		가운데 맵의 가운데 좌표를 기준으로 position을 반환
	*/
	Vec2	getPosition();

	/**
		맵의 화면상 좌표를 vec만큼 이동
	*/
	void	moveMapPosition(Vec2 vec);

private:
	MapManager();
	MapManager(const MapManager& other);
	static MapManager*						_instance;
	std::map<int, NodeTileMap*>				_mapsForNodesWithIndex;

	/**
		현재 메모리에 올라있는 9개의 칸
	*/
	std::map<DirectionKind, NodeTileMap*>	_nineZones;

	/**
		사용자가 addchild하기 위한 핸들
	*/
	Node*	_handle = nullptr;

	/**
		가운데 칸을 중심으로 맵을 정렬한다.
	*/
	void	reposition();

	/**
		반대편 posNum을 반환
		posNum : 해당 좌표
		direction : 해당 타일이 어느쪽 외곽선인지 입력
	*/
	unsigned	getOppositeZoneNumber(unsigned posNum, DirectionKind direction);
};