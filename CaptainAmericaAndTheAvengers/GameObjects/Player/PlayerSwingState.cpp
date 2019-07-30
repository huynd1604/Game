#include "PlayerSwingState.h"
#include "Player.h"
#include "PlayerStandingState.h"
#include "../../GameDefines/GameDefine.h"

PlayerSwingState::PlayerSwingState(PlayerData *playerData)
{
    this->mPlayerData = playerData;
    this->mPlayerData->player->SetVx(0);
    this->mPlayerData->player->SetVy(0);
	if (this->mPlayerData->player->mShield->getState() != ShieldState::StateName::Attack)
	{
		this->mPlayerData->player->mShield->SetState(ShieldState::StateName::Jumping2);
	}
}


PlayerSwingState::~PlayerSwingState()
{
}

void PlayerSwingState::Update(float dt)
{
	//if (this->mPlayerData->player->IsLastAnimation())
	//{
	//	this->mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData));
	//	return;
	//}
}

void PlayerSwingState::HandleKeyboard(std::map<int, bool> keys)
{
    
}

PlayerState::StateName PlayerSwingState::GetState()
{
	return PlayerState::Swing;
}
