#include "PlayerAttackShield.h"
#include "Player.h"
#include "PlayerStandingState.h"
#include "../../GameDefines/GameDefine.h"

PlayerAttackShield::PlayerAttackShield(PlayerData *playerData)
{
    this->mPlayerData = playerData;
    this->mPlayerData->player->SetVx(0);
    this->mPlayerData->player->SetVy(0);
}


PlayerAttackShield::~PlayerAttackShield()
{
}

void PlayerAttackShield::Update(float dt)
{
	if (this->mPlayerData->player->IsLastAnimation())
	{
		this->mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData));
		return;
	}
}

void PlayerAttackShield::HandleKeyboard(std::map<int, bool> keys)
{
    
}

PlayerState::StateName PlayerAttackShield::GetState()
{
    return PlayerState::AttackShield;
}
