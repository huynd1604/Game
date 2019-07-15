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
