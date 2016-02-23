#pragma once

/**
키보드 우측 숫자패드가 방향 기준
*/
enum DirectionKind{
	DIRECTION_1,
	DIRECTION_2,
	DIRECTION_3,
	DIRECTION_4,
	DIRECTION_N,//중립
	DIRECTION_6,
	DIRECTION_7,
	DIRECTION_8,
	DIRECTION_9
};
#define MAX_DIRECTION DIRECTION_9+1

static const unsigned SCREEN_PIXEL_WIDTH = 1024;
static const unsigned SCREEN_PIXEL_HEIGHT = 768;
static const unsigned WORLD_MAP_SIZE_WIDTH = 4;
static const unsigned WORLD_MAP_SIZE_HEIGHT = 4;
