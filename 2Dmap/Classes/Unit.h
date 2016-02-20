#pragma once
class Unit : public cocos2d::Node
{
public:
	Unit();
	virtual ~Unit();
	static void createUnit();
protected:
	cocos2d::Sprite*	_sprite;
private:
	CC_SYNTHESIZE(cocos2d::Point, _position, PositionOfUnit)
};