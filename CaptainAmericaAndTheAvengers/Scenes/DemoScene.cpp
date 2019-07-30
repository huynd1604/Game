#include "DemoScene.h"
#include <fstream>
#include "../GameComponents/GameColision.h"
#include "../GameObjects/Player/PlayerFallingState.h"
DemoScene::DemoScene()
{
    LoadContent();
}

void DemoScene::LoadContent()
{
	//set mau backcolor cho scene o day la mau xanh
	mBackColor = 0x54acd2;
	mDebugDraw = new GameDebugDraw();
	mMap = new GameMap("Resources/map/map1.txt", "Resources/map/map1.png");
	int ID = 0;
	for (int i = 0; i < mMap->GetWidth(); i += Define::GRID_WIDTH)
	{
		for (int j = 0; j < mMap->GetHeight(); j += Define::GRID_WIDTH)
		{
			GameGrid* grid = new GameGrid();
			grid->PosX = i;
			grid->PosY = j;
			grid->ID = ID;
			listGrid.push_back(grid);
		}
	}
	std::ifstream in;

	in.open("Resources/map/MapObject.txt");
	int item;

	if (in.is_open())
	{
		while (!in.eof())
		{
			string type;
			int ID, posX, posY, w, h;
			in >> type;
			in >> ID;
			in >> posX;
			in >> posY;
			in >> w;
			in >> h;
			if (type == "land")
			{
				Entity* temp = new Entity();
				posX = (posX + posX + w) / 2;
				posY = (posY + posY + h) / 2;
				temp->SetPosition(D3DXVECTOR3(posX, posY, 0));
				temp->SetHeight(h);
				temp->SetWidth(w);
				temp->SetVx(0);
				temp->SetVy(0);
				temp->Tag = Entity::EntityTypes::None;
				listGameObject.push_back(temp);
				for (int i = 0; i < listGrid.size(); i++)
				{
					if (GameGlobal::isCollide(temp->GetBound(), listGrid[i]->getRect()))
					{
						listGrid[i]->AddObject(listGameObject.size() - 1);
					}
				}
			}
		}
	}
	


	mCamera = new Camera(GameGlobal::GetWidth(), GameGlobal::GetHeight());
	mCamera->SetPosition(GameGlobal::GetWidth() / 2,
		mMap->GetHeight() - mCamera->GetHeight()+ mCamera->GetHeight()/2);

	mMap->SetCamera(mCamera);


	Player::GetInstance()->SetPosition(Player::GetInstance()->GetBound().right + 20, 200);
	Player::GetInstance()->SetCamera(mCamera);
}

void DemoScene::Update(float dt)
{
    Player::GetInstance()->HandleKeyboard(keys);
    Player::GetInstance()->Update(dt);
	for (int i = 0; i < listGrid.size(); i++)
	{
		if (GameGlobal::isCollide(mCamera->GetBound(),listGrid[i]->getRect()))
		{
			std::vector<int> vt = listGrid[i]->GetListObject();
			float a = 0;
			bool canStand = false;
			for (int j = 0; j < vt.size(); j++)
			{
				eDirection ac;
				 a = GameColision::sweptAABB(Player::GetInstance()->GetBound(),
					Player::GetInstance()->GetVx()*dt,
					Player::GetInstance()->GetVy()*dt,
					listGameObject[vt[j]]->GetBound(), ac);
				if (a >= 0.0f&&a < 1.0f)
				{
					Player::GetInstance()->AddPosition(D3DXVECTOR2(Player::GetInstance()->GetVx()*a*dt,
						Player::GetInstance()->GetVy()*a*dt));
					Player::GetInstance()->OnColision(listGameObject[vt[j]]->Tag,ac, a*dt);
				}
				
				
			}
			for (int j = 0; j < listGameObject.size(); j++)
			{
				if (listGameObject[j]->Tag == Entity::EntityTypes::None)
				{
					if (Player::GetInstance()->GetBound().left > listGameObject[j]->GetBound().left - Player::GetInstance()->GetWidth() &&
						Player::GetInstance()->GetBound().right < listGameObject[j]->GetBound().right + Player::GetInstance()->GetWidth() &&
						Player::GetInstance()->GetBound().bottom == listGameObject[j]->GetBound().top)
					{
						canStand = true;
					}
				}
			}
			if (!canStand)
			{
				if (Player::GetInstance()->getState()== PlayerState::Running)
				{
					Player::GetInstance()->SetState(new PlayerFallingState(Player::GetInstance()->mPlayerData));
				}
			}
		}
	}
	
	CheckCameraAndWorldMap();

}

void DemoScene::Draw()
{
	mMap->Draw();
	Player::GetInstance()->Draw();
	mCamera->SetPosition(Player::GetInstance()->GetPosition().x,
		mCamera->GetPosition().y);
	mDebugDraw->setLineSize(3);
	for (int i = 0; i < listGrid.size(); i++)
	{
		mDebugDraw->DrawRect(listGrid[i]->getRect());
		
	}
	for (int j = 0; j < listGameObject.size(); j++)
	{
		mDebugDraw->DrawRect(listGameObject[j]->GetBound(), mCamera);
	}
	mDebugDraw->DrawRect(Player::GetInstance()->GetBound(),mCamera);
}

void DemoScene::OnKeyDown(int keyCode)
{
    keys[keyCode] = true;

    Player::GetInstance()->OnKeyPressed(keyCode);
}

void DemoScene::OnKeyUp(int keyCode)
{
    keys[keyCode] = false;
	Player::GetInstance()->OnKeyUp(keyCode);
}

void DemoScene::OnMouseDown(float x, float y)
{
}
void DemoScene::CheckCameraAndWorldMap()
{
	mCamera->SetPosition(Player::GetInstance()->GetPosition());

	if (mCamera->GetBound().left < 0)
	{
		//vi position cua camera ma chinh giua camera
		//luc nay o vi tri goc ben trai cua the gioi thuc
		mCamera->SetPosition(mCamera->GetWidth() / 2, mCamera->GetPosition().y);
	}

	if (mCamera->GetBound().right > mMap->GetWidth())
	{
		//luc nay cham goc ben phai cua the gioi thuc
		mCamera->SetPosition(mMap->GetWidth() - mCamera->GetWidth() / 2,
			mCamera->GetPosition().y);
	}

	if (mCamera->GetBound().top < 0)
	{
		//luc nay cham goc tren the gioi thuc
		mCamera->SetPosition(mCamera->GetPosition().x, mCamera->GetHeight() / 2);
	}

	if (mCamera->GetBound().bottom > mMap->GetHeight())
	{
		//luc nay cham day cua the gioi thuc
		mCamera->SetPosition(mCamera->GetPosition().x,
			mMap->GetHeight() - mCamera->GetHeight() / 2);
	}
}