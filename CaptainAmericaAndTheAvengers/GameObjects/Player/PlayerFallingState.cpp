#include "PlayerFallingState.h"
#include "Player.h"
#include "PlayerStandingState.h"
#include "../../GameDefines/GameDefine.h"

PlayerFallingState::PlayerFallingState(PlayerData *playerData)
{
    this->mPlayerData = playerData;
    acceleratorY = 10.0f;
    acceleratorX = 3.0f;
	mPlayerData->player->SetVy(130);
	if (this->mPlayerData->player->mShield->getState() != ShieldState::StateName::Attack)
	{
		this->mPlayerData->player->mShield->SetState(ShieldState::StateName::Jumping);
	}
    if (this->mPlayerData->player->GetVx() == 0)
    {
        allowMoveX = false;
    }
    else
    {
        allowMoveX = true;
    }
}


PlayerFallingState::~PlayerFallingState()
{
}

void PlayerFallingState::Update(float dt)
{
    //this->mPlayerData->player->AddVy(acceleratorY);

   /* if (mPlayerData->player->GetVy() > GameGlobal::MaxJum)
    {
        mPlayerData->player->SetVy(GameGlobal::MaxJum);
    }*/
	/*if (this->mPlayerData->player->GetPosition().y >= 415)
	{
		this->mPlayerData->player->SetPosition(
			this->mPlayerData->player->GetPosition().x,
			415
		);
		this->mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData));
	}*/
}

void PlayerFallingState::HandleKeyboard(std::map<int, bool> keys)
{
    if (keys[VK_RIGHT])
    {
        mPlayerData->player->SetReverse(false);

        isLeftOrRightKeyPressed = true;
        //di chuyen sang phai
        if (this->mPlayerData->player->GetVx() < Define::PLAYER_MAX_RUNNING_SPEED)
        {
            this->mPlayerData->player->AddVx(acceleratorX);

            if (this->mPlayerData->player->GetVx() >= Define::PLAYER_MAX_RUNNING_SPEED)
            {
                this->mPlayerData->player->SetVx(Define::PLAYER_MAX_RUNNING_SPEED);
            }
        }
    }
    else if (keys[VK_LEFT])
    {
        mPlayerData->player->SetReverse(true);

        isLeftOrRightKeyPressed = true;
        //di chuyen sang trai
        if (this->mPlayerData->player->GetVx() > -Define::PLAYER_MAX_RUNNING_SPEED)
        {
            this->mPlayerData->player->AddVx(-acceleratorX);

            if (this->mPlayerData->player->GetVx() <= -Define::PLAYER_MAX_RUNNING_SPEED)
            {
                this->mPlayerData->player->SetVx(-Define::PLAYER_MAX_RUNNING_SPEED);
            }
        }
    }
    else
    {
        isLeftOrRightKeyPressed = false;    
    }
}

void PlayerFallingState::OnCollision(Entity::EntityTypes type, eDirection dir, float dt)
{
	switch (type)
	{
	case Entity::None:
		if (dir == eDirection::DOWN)
		{
			//mPlayerData->player->AddPosition(D3DXVECTOR2(0, -dt));
			this->mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData));
		}
		else if (dir == eDirection::RIGHT || dir == eDirection::LEFT)
		{
			mPlayerData->player->SetVx(0);
		}
		break;
	default:
		break;
	}
}

PlayerState::StateName PlayerFallingState::GetState()
{
    return PlayerState::Falling;
}
