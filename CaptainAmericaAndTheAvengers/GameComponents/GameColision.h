#pragma once
#include "GameGlobal.h"
enum eDirection
{
	RIGHT,
	LEFT,
	UP,
	DOWN
};
class GameColision
{
private:
	static bool isColliding(const RECT &object, const RECT &other);
public:
	static float sweptAABB(const RECT& object, const float ObVx, const float ObVy,
		const RECT& other, eDirection& result);
	GameColision();
	~GameColision();
};

