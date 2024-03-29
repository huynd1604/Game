#include "PlayerJumping2State.h"
#include "PlayerStandingState.h"
#include "PlayerFallingState.h"
#include "../../GameDefines/GameDefine.h"

PlayerJumping2State::PlayerJumping2State(PlayerData *playerData)
{
    this->mPlayerData = playerData;
	GameGlobal::MinJum = Define::PLAYER_MIN_JUMP_VELOCITY;
	GameGlobal::MaxJum = Define::PLAYER_MAX_JUMP_VELOCITY;
	this->mPlayerData->player->SetOldPosition(this->mPlayerData->player->GetPosition());
	if (this->mPlayerData->player->mShield->getState() != ShieldState::StateName::Attack)
	{
		this->mPlayerData->player->mShield->SetState(ShieldState::StateName::Jumping2);
	}
	this->mPlayerData->player->SetVy(GameGlobal::MinJum);

    acceleratorY = 5.0f;
    acceleratorX = 6.0f;

    noPressed = false;
}


PlayerJumping2State::~PlayerJumping2State()
{

}

void PlayerJumping2State::Update(float dt)
{
	this->mPlayerData->player->AddVy(acceleratorY);

	if (mPlayerData->player->GetVy() >= 0)
	{
		mPlayerData->player->SetState(new PlayerFallingState(this->mPlayerData));

		return;
	}


    if (noPressed)
    {
        if (mPlayerData->player->getMoveDirection() == Player::MoveToLeft)
        {
			//this->mPlayerData->player->SetVx(Define::PLAYER_MAX_RUNNING_SPEED);
			////player dang di chuyen sang ben trai      
            if (mPlayerData->player->GetVx() < 0)
            {
                this->mPlayerData->player->AddVx(acceleratorX);

                if (mPlayerData->player->GetVx() > 0)
                    this->mPlayerData->player->SetVx(0);
            }
        }
        else if (mPlayerData->player->getMoveDirection() == Player::MoveToRight)
        {
			//this->mPlayerData->player->SetVx(-Define::PLAYER_MAX_RUNNING_SPEED);
			////player dang di chuyen sang phai   
            if (mPlayerData->player->GetVx() > 0)
            {
                this->mPlayerData->player->AddVx(-acceleratorX);

                if (mPlayerData->player->GetVx() < 0)
                    this->mPlayerData->player->SetVx(0);
            }
        }
    }
}

void PlayerJumping2State::HandleKeyboard(std::map<int, bool> keys)
{
    if (keys[VK_RIGHT])
    {
        mPlayerData->player->SetReverse(false);

        //di chuyen sang phai
        if (this->mPlayerData->player->GetVx() < Define::PLAYER_MAX_RUNNING_SPEED)
        {
            this->mPlayerData->player->AddVx(acceleratorX);

            if (this->mPlayerData->player->GetVx() >= Define::PLAYER_MAX_RUNNING_SPEED)
            {
                this->mPlayerData->player->SetVx(Define::PLAYER_MAX_RUNNING_SPEED);
            }
        }

        noPressed = false;
    }
    else if (keys[VK_LEFT])
    {
        mPlayerData->player->SetReverse(true);

        //di chuyen sang trai
        if (this->mPlayerData->player->GetVx() > -Define::PLAYER_MAX_RUNNING_SPEED)
        {
            this->mPlayerData->player->AddVx(-acceleratorX);

            if (this->mPlayerData->player->GetVx() < -Define::PLAYER_MAX_RUNNING_SPEED)
            {
                this->mPlayerData->player->SetVx(-Define::PLAYER_MAX_RUNNING_SPEED);
            }
        }

        noPressed = false;
    }
    else
    {
        noPressed = true;
    }
}

PlayerState::StateName PlayerJumping2State::GetState()
{
    return PlayerState::Jumping2;
}
