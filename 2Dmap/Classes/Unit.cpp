#include "pch.h"
#include "Unit.h"


Unit::Unit()
{
	_sprite = cocos2d::Sprite::create();
	this->addChild(_sprite);
}


Unit::~Unit()
{
}