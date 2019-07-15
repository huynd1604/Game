#include "PlayerStandingState.h"
#include "Player.h"
#include "PlayerFallingState.h"
#include "PlayerTopDefState.h"
#include "PlayerAttackShield.h"
#include "../../GameDefines/GameDefine.h"

PlayerStandingState::PlayerStandingState(PlayerData *playerData)
{
    this->mPlayerData = playerData;
    this->mPlayerData->player->SetVx(0);
    this->mPlayerData->player->SetVy(0);
	this->mPlayerData->player->mShield->SetPosition(this->mPlayerData->player->GetPosition());
	this->mPlayerData->player->mShield->SetVx(0);
	this->mPlayerData->player->mShield->SetVy(0);

}


PlayerStandingState::~PlayerStandingState()
{
}

void PlayerStandingState::Update(float dt)
{

}

void PlayerStandingState::HandleKeyboard(std::map<int, bool> keys)
{
    if (keys[VK_LEFT] || keys[VK_RIGHT])
    {
        this->mPlayerData->player->SetState(new PlayerRunningState(this->mPlayerData));
        return;
	}
	
}

PlayerState::StateName PlayerStandingState::GetState()
{
    return PlayerState::Standing;
}
