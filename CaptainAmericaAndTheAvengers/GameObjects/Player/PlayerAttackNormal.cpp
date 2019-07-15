#include "PlayerAttackNormal.h"
#include "Player.h"
#include "PlayerStandingState.h"
#include "../../GameDefines/GameDefine.h"

PlayerAttackNormal::PlayerAttackNormal(PlayerData *playerData)
{
    this->mPlayerData = playerData;
    this->mPlayerData->player->SetVx(0);
    this->mPlayerData->player->SetVy(0);
}


PlayerAttackNormal::~PlayerAttackNormal()
{
}

void PlayerAttackNormal::Update(float dt)
{
	if (this->mPlayerData->player->IsLastAnimation())
	{
		this->mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData));
		return;
	}
}

void PlayerAttackNormal::HandleKeyboard(std::map<int, bool> keys)
{
    
}

PlayerState::StateName PlayerAttackNormal::GetState()
{
    return PlayerState::AttackNormal;
}
