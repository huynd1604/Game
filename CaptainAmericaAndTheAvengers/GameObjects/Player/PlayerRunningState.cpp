#include "PlayerRunningState.h"
#include "PlayerStandingState.h"
#include "PlayerFallingState.h"
#include "../../GameDefines/GameDefine.h"
#include "../Shield/ShieldData.h"

PlayerRunningState::PlayerRunningState(PlayerData *playerData)
{
    this->mPlayerData = playerData;
	if (this->mPlayerData->player->mShield->getState() != ShieldState::StateName::Attack)
	{
		this->mPlayerData->player->mShield->SetState(ShieldState::StateName::Running);
	}
    acceleratorX = 8.0f; 
}


PlayerRunningState::~PlayerRunningState()
{
}

void PlayerRunningState::Update(float dt)
{

}

void PlayerRunningState::HandleKeyboard(std::map<int, bool> keys)
{
    if (keys[VK_RIGHT])
    {
        mPlayerData->player->SetReverse(false);

		//this->mPlayerData->player->SetVx(Define::PLAYER_MAX_RUNNING_SPEED);
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
		//this->mPlayerData->player->SetVx(-Define::PLAYER_MAX_RUNNING_SPEED);
        ////di chuyen sang trai
        if (this->mPlayerData->player->GetVx() > -Define::PLAYER_MAX_RUNNING_SPEED)
        {
            this->mPlayerData->player->AddVx(-acceleratorX);

            if (this->mPlayerData->player->GetVx() < -Define::PLAYER_MAX_RUNNING_SPEED)
            {
				
            }
        }
    }
    else
    {
        this->mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData));
        return;
    }
}

PlayerState::StateName PlayerRunningState::GetState()
{
    return PlayerState::Running;
}
void PlayerRunningState::OnCollision(Entity::EntityTypes type, eDirection dir, float dt)
{
	switch (type)
	{
	case Entity::None:
		if (dir == eDirection::DOWN)
		{
			//mPlayerData->player->AddPosition(D3DXVECTOR2(0, -2));
			this->mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData));
		}
		else if (dir == eDirection::RIGHT )
		{
			mPlayerData->player->AddPosition(D3DXVECTOR2(-2,0));
			mPlayerData->player->SetVx(0);
			this->mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData));
		}
		else if ( dir == eDirection::LEFT)
		{
			mPlayerData->player->AddPosition(D3DXVECTOR2(2, 0));
			mPlayerData->player->SetVx(0);
			this->mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData));
		}
		break;
	default:
		break;
	}
}