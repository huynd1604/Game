#include "GameGrid.h"
#include "../GameDefines/GameDefine.h"
using namespace std;

GameGrid::GameGrid()
{

}

GameGrid::~GameGrid()
{

}

void GameGrid::AddObject(int entity)
{
	listObject.push_back(entity);
}
vector<int> GameGrid::GetListObject()
{
	return listObject;
}

RECT GameGrid::getRect()
{
	RECT gridRect;
	gridRect.left = PosX;
	gridRect.top = PosY;
	gridRect.bottom = PosY + Define::GRID_HEIGHT;
	gridRect.right = PosX + Define::GRID_WIDTH;
	return gridRect;
}