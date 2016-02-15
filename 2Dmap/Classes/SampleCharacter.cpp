#include "pch.h"
#include "SampleCharacter.h"


SampleCharacter::SampleCharacter()
{
	_sprite->initWithFile("testSprite.png", cocos2d::Rect(0, 0, 32, 48));
	_sprite->setAnchorPoint(cocos2d::Vec2(0.5, 44 / 48));
}


SampleCharacter::~SampleCharacter()
{
}
