#include "PlayerSittingAttackState.h"
#include "Player.h"
#include "PlayerFallingState.h"
#include "PlayerTopDefState.h"
#include "PlayerAttackShield.h"
#include "../../GameDefines/GameDefine.h"

PlayerSittingAttackState::PlayerSittingAttackState(PlayerData *playerData)
{
    this->mPlayerData = playerData;
    this->mPlayerData->player->SetVx(0);
    this->mPlayerData->player->SetVy(0);
}


PlayerSittingAttackState::~PlayerSittingAttackState()
{
}

void PlayerSittingAttackState::Update(float dt)
{

}

void PlayerSittingAttackState::HandleKeyboard(std::map<int, bool> keys)
{
    if (keys[VK_LEFT] || keys[VK_RIGHT])
    {
        this->mPlayerData->player->SetState(new PlayerRunningState(this->mPlayerData));
        return;
	}
	
}

PlayerState::StateName PlayerSittingAttackState::GetState()
{
    return PlayerState::AttackSitting;
}
