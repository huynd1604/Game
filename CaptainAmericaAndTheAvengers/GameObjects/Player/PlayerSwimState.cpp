#include "PlayerSwimState.h"
#include "Player.h"
#include "PlayerStandingState.h"
#include "../../GameDefines/GameDefine.h"

PlayerSwimState::PlayerSwimState(PlayerData *playerData)
{
    this->mPlayerData = playerData;
    this->mPlayerData->player->SetVx(0);
    this->mPlayerData->player->SetVy(0);
	if (this->mPlayerData->player->mShield->getState() != ShieldState::StateName::Attack)
	{
		this->mPlayerData->player->mShield->SetState(ShieldState::StateName::Jumping2);
	}
}


PlayerSwimState::~PlayerSwimState()
{
}

void PlayerSwimState::Update(float dt)
{
	if (this->mPlayerData->player->IsLastAnimation())
	{
		this->mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData));
		return;
	}
}

void PlayerSwimState::HandleKeyboard(std::map<int, bool> keys)
{
    
}

PlayerState::StateName PlayerSwimState::GetState()
{
    return PlayerState::AttackNormal;
}
