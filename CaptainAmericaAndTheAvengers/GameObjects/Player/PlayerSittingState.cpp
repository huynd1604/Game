#include "PlayerSittingState.h"
#include "Player.h"
#include "PlayerFallingState.h"
#include "PlayerTopDefState.h"
#include "PlayerAttackShield.h"
#include "../../GameDefines/GameDefine.h"

PlayerSittingState::PlayerSittingState(PlayerData *playerData)
{
    this->mPlayerData = playerData;
    this->mPlayerData->player->SetVx(0);
    this->mPlayerData->player->SetVy(0);
	if (this->mPlayerData->player->mShield->getState() != ShieldState::StateName::Attack)
	{
		this->mPlayerData->player->mShield->SetState(ShieldState::StateName::Standing);
	}
}


PlayerSittingState::~PlayerSittingState()
{
}

void PlayerSittingState::Update(float dt)
{

}

void PlayerSittingState::HandleKeyboard(std::map<int, bool> keys)
{
    if (keys[VK_LEFT] || keys[VK_RIGHT])
    {
        this->mPlayerData->player->SetState(new PlayerRunningState(this->mPlayerData));
        return;
	}
	
}

PlayerState::StateName PlayerSittingState::GetState()
{
    return PlayerState::Sitting;
}
