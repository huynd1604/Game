#include "PlayerTopDefState.h"
#include "Player.h"
#include "PlayerFallingState.h"
#include "../../GameDefines/GameDefine.h"

PlayerTopDefState::PlayerTopDefState(PlayerData *playerData)
{
    this->mPlayerData = playerData;
    this->mPlayerData->player->SetVx(0);
    this->mPlayerData->player->SetVy(0);
}


PlayerTopDefState::~PlayerTopDefState()
{
}

void PlayerTopDefState::Update(float dt)
{

}

void PlayerTopDefState::HandleKeyboard(std::map<int, bool> keys)
{
    if (keys[VK_LEFT] || keys[VK_RIGHT])
    {
        this->mPlayerData->player->SetState(new PlayerRunningState(this->mPlayerData));
        return;
    }
}

PlayerState::StateName PlayerTopDefState::GetState()
{
    return PlayerState::TopDef;
}
