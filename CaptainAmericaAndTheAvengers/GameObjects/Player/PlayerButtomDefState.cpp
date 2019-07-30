#include "PlayerButtomDefState.h"
#include "Player.h"
#include "PlayerStandingState.h"
#include "../../GameDefines/GameDefine.h"

PlayerButtomDefState::PlayerButtomDefState(PlayerData *playerData)
{
    this->mPlayerData = playerData;
    this->mPlayerData->player->SetVx(0);
	if (this->mPlayerData->player->mShield->getState() != ShieldState::StateName::Attack)
	{
		this->mPlayerData->player->mShield->SetState(ShieldState::StateName::Jumping2);
	}
}


PlayerButtomDefState::~PlayerButtomDefState()
{
}

void PlayerButtomDefState::Update(float dt)
{
	this->mPlayerData->player->AddVy(20.0f);
	if (mPlayerData->player->GetVy() > GameGlobal::MaxJum)
	{
		mPlayerData->player->SetVy(GameGlobal::MaxJum);
	}
	if (this->mPlayerData->player->GetPosition().y >= 415)
	{
		this->mPlayerData->player->SetPosition(
			this->mPlayerData->player->GetPosition().x,
			415
		);
		this->mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData));
	}
}

void PlayerButtomDefState::HandleKeyboard(std::map<int, bool> keys)
{
    
}

PlayerState::StateName PlayerButtomDefState::GetState()
{
    return PlayerState::ButtomDef;
}
