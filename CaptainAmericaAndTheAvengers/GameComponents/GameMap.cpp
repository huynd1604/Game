#include "GameMap.h"
#include <fstream>


GameMap::GameMap(char * filePath, char * fileTileSet)
{
	LoadMap(filePath, fileTileSet);
}

GameMap::~GameMap()
{
	for (int i = 0; i < mRow; i++)
	{
		if (mMatrixMap[i] != NULL)
		{
			delete mMatrixMap[i];
		}
	}
	delete mMatrixMap;

}

void GameMap::LoadMap(char* filePath, char* fileTileSet)
{
	mapSprite = new Sprite(fileTileSet);
	std::ifstream in;

	in.open(filePath);
	int item;

	if (in.is_open())
	{
		in >> mWidth;
		in >> mHeight;
		in >> mRow;
		in >> mColumn;

		if (mMatrixMap == NULL)
		{
			this->mMatrixMap = new int*[mRow];
			for (int i = 0; i < mRow; i++)
			{
				mMatrixMap[i] = new int[mColumn];
				for (int j = 0; j < mColumn; j++)
				{
					in >> item;
					mMatrixMap[i][j] = item;
				}
			}
		}
	}
}


bool GameMap::isContain(RECT rect1, RECT rect2)
{
    if (rect1.left > rect2.right || rect1.right < rect2.left || rect1.top > rect2.bottom || rect1.bottom < rect2.top)
    {
        return false;
    }

    return true;
}


int GameMap::GetWidth()
{
	return mColumn*mWidth;
}

int GameMap::GetHeight()
{
	return mRow*mHeight;
}

int GameMap::GetTileWidth()
{
	return mWidth;
}

int GameMap::GetTileHeight()
{
	return mHeight;
}

void GameMap::Draw()
{
    D3DXVECTOR2 trans = D3DXVECTOR2(GameGlobal::GetWidth() / 2 - mCamera->GetPosition().x,
                                    GameGlobal::GetHeight() / 2 - mCamera->GetPosition().y);
	RECT spriteRec;
	for (int i = 0; i < mRow; i++)
	{
		for (int j = 0; j < mColumn; j++)
		{
			spriteRec.top = 0;
			spriteRec.bottom = mHeight;
			spriteRec.left = mMatrixMap[i][j] * mWidth;
			spriteRec.right = spriteRec.left + mWidth;

			D3DXVECTOR3 position(j*mWidth,i*mHeight, 0);
			if (mCamera != NULL)
			{
				RECT objRECT;
				objRECT.left = position.x - mWidth / 2;
				objRECT.top = position.y - mHeight / 2;
				objRECT.right = objRECT.left + mWidth;
				objRECT.bottom = objRECT.top + mHeight;
				RECT cameraRECT = mCamera->GetBound();
				cameraRECT.left -= 10;
				cameraRECT.top -= 10;
				cameraRECT.right += 10;
				cameraRECT.bottom == 10;
				if (isContain(objRECT, cameraRECT) == false)
					continue;
			}
			mapSprite->Draw(position, spriteRec, D3DXVECTOR2(), trans, 0, D3DXVECTOR2(),D3DCOLOR_XRGB(255, 255, 255), D3DXVECTOR3(0.0f,0.0f,0.0f));
		}
	}
   
}

void GameMap::SetCamera(Camera * camera)
{
    this->mCamera = camera;
}
