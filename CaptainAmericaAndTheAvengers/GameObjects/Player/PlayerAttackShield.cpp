#include "PlayerAttackShield.h"
#include "Player.h"
#include "PlayerStandingState.h"
#include "../../GameDefines/GameDefine.h"

PlayerAttackShield::PlayerAttackShield(PlayerData *playerData)
{
    this->mPlayerData = playerData;
	this->mPlayerData->player->SetOldPosition(this->mPlayerData->player->GetPosition());
	this->mPlayerData->player->SetVx(0);
    this->mPlayerData->player->SetVy(0);
	this->mPlayerData->player->mShield->SetState(ShieldState::StateName::Jumping2);
}


PlayerAttackShield::~PlayerAttackShield()
{
}

void PlayerAttackShield::Update(float dt)
{
	if (this->mPlayerData->player->IsLastAnimation())
	{
		this->mPlayerData->player->mShield->SetPosition(this->mPlayerData->player->GetPosition() + this->mPlayerData->player->GetShieldAdd());
		this->mPlayerData->player->mShield->SetState(ShieldState::StateName::Attack);
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
