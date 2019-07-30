#pragma once
#ifndef __GAME_MAP__
#define __GAME_MAP__

#include <d3dx9.h>
#include <d3d9.h>
#include <vector>
#include <set>
#include <vector>

#include "Sprite.h"
#include "../MapReader/Tmx.h.in"
#include "GameGlobal.h"
#include "../GameComponents/Camera.h"
#include "../GameDefines/GameDefine.h"

class GameMap
{
public:
	GameMap(char* filePath, char* fileTileSet = "");


    int GetWidth();
    int GetHeight();
    int GetTileWidth();
    int GetTileHeight();

    void SetCamera(Camera *camera);

    void Draw();    

    ~GameMap();

private:

    void LoadMap(char* filePath, char* fileTileSet = "");
    bool isContain(RECT rect1, RECT rect2);

	Sprite* mapSprite;
	int** mMatrixMap;
	int mWidth, mHeight;
	int mColumn, mRow;
    Camera *mCamera;
};

#endif

