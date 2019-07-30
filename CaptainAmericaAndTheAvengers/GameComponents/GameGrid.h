#include "../GameObjects/Entity.h"
#include <vector>

class GameGrid
{
public:

	int ID;
	float PosX, PosY;
	GameGrid();
	~GameGrid();

	void AddObject(int entity);
	RECT getRect();
	std::vector<int> GetListObject();

protected:
	std::vector<int> listObject;

};
