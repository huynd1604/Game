#include "GameColision.h"
#include "GameGlobal.h"
#include <limits>


bool GameColision::isColliding(const RECT & rect1, const RECT & rect2)
{
	if (rect1.left > rect2.right || rect1.right < rect2.left || rect1.top > rect2.bottom || rect1.bottom < rect2.top)
	{
		return false;
	}

	return true;

}

float GameColision::sweptAABB(const RECT & object, const float ObVx, const float ObVy, const RECT & other, eDirection& result)
{
	float dxEntry, dxExit;
	float dyEntry, dyExit;
	float txEntry, txExit;
	float tyEntry, tyExit;
	float entryTime;
	float exitTime;
	RECT rect;
	rect.left = ObVx > 0 ? object.left : object.left + ObVx;
	rect.top = ObVy > 0 ? object.top : object.top + ObVy;
	rect.right = object.right - object.left + rect.left + abs(ObVx);
	rect.bottom = object.bottom - object.top + rect.top + abs(ObVy);
	if (!isColliding(rect, other))
	{
		return 1.0f;
	}
	if (ObVx > 0.0f)
	{
		dxEntry = other.left - object.right;
		dxExit = other.right - object.left;
	}
	else
	{
		dxEntry = other.right - object.left;
		dxExit = other.left - object.right;
	}

	if (ObVy > 0.0f)
	{
		dyEntry = other.top - object.bottom;
		dyExit = other.bottom - object.top;
	}
	else
	{
		dyEntry = other.bottom - object.top;
		dyExit = other.top - object.bottom;
	}

	if (ObVx == 0.0f)
	{
		txEntry = -std::numeric_limits<float>::infinity();
		txExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		txEntry = dxEntry / ObVx;
		txExit = dxExit / ObVx;
	}

	if (ObVy == 0.0f)
	{
		tyEntry = -std::numeric_limits<float>::infinity();
		tyExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		tyEntry = dyEntry / ObVy;
		tyExit = dyExit / ObVy;
	}

	entryTime = max(txEntry, tyEntry);
	exitTime = min(txExit, tyExit);

	if (entryTime > exitTime || (txEntry < 0.0f && tyEntry < 0.0f) || txEntry > 1.0f || tyEntry > 1.0f)
	{
		return 1.0f;
	}
	if (txEntry > tyEntry)
	{
		if (dxEntry > 0.0f)
		{
			result = eDirection::RIGHT;
		}
		else if(dxEntry < 0.0f)
		{
			result = eDirection::LEFT;
		}
		else
		{
			if (ObVx > 0.0f)
			{
				result = eDirection::RIGHT;
			}
			else 
			{
				result = eDirection::LEFT;
			}
		}
	}
	else
	{
		if (dyEntry < 0.0f)
		{
			result = eDirection::UP;
		}
		else if (dyEntry > 0.0f)
		{
			result = eDirection::DOWN;
		}
		else
		{
			if (ObVy < 0.0f)
			{
				result = eDirection::UP;
			}
			else if (ObVy > 0.0f)
			{
				result = eDirection::DOWN;
			}
		}
	}
	return entryTime;
}

GameColision::GameColision()
{
}


GameColision::~GameColision()
{
}
