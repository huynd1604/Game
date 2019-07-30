#include "PlayerSurfingState.h"
#include "Player.h"
#include "PlayerStandingState.h"
#include "../../GameDefines/GameDefine.h"

PlayerSurfingState::PlayerSurfingState(PlayerData *playerData)
{
    this->mPlayerData = playerData;
    this->mPlayerData->player->SetVx(0);
    this->mPlayerData->player->SetVy(0);
	if (this->mPlayerData->player->mShield->getState() != ShieldState::StateName::Attack)
	{
		this->mPlayerData->player->mShield->SetState(ShieldState::StateName::Jumping2);
	}
}


PlayerSurfingState::~PlayerSurfingState()
{
}

void PlayerSurfingState::Update(float dt)
{

		if (this->mPlayerData->player->GetVx() < Define::PLAYER_MAX_RUNNING_SPEED)
		{
			this->mPlayerData->player->AddVx(30.0f);

			if (this->mPlayerData->player->GetVx() >= Define::PLAYER_MAX_RUNNING_SPEED)
			{
				this->mPlayerData->player->SetVx(Define::PLAYER_MAX_RUNNING_SPEED);
			}
		}
	
	if (this->mPlayerData->player->IsLastAnimation())
	{
		this->mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData));
		return;
	}
}

void PlayerSurfingState::HandleKeyboard(std::map<int, bool> keys)
{
    
}

PlayerState::StateName PlayerSurfingState::GetState()
{
    return PlayerState::Surfing;
}
