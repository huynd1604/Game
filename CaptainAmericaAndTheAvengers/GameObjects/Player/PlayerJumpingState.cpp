#include "PlayerJumpingState.h"
#include "PlayerStandingState.h"
#include "PlayerFallingState.h"
#include "PlayerJumping2State.h"
#include "../../GameDefines/GameDefine.h"

PlayerJumpingState::PlayerJumpingState(PlayerData *playerData)
{
    this->mPlayerData = playerData;
	GameGlobal::MaxJum = Define::PLAYER_MAX_JUMP_VELOCITY - 20;
	GameGlobal::MinJum = Define::PLAYER_MIN_JUMP_VELOCITY + 20;
	this->mPlayerData->player->SetVy(GameGlobal::MinJum);
	this->mPlayerData->player->SetOldPosition(this->mPlayerData->player->GetPosition());
	acceleratorY = 5.0f;
    acceleratorX = 6.0f;
	if (this->mPlayerData->player->mShield->getState() != ShieldState::StateName::Attack)
	{
		this->mPlayerData->player->mShield->SetState(ShieldState::StateName::Jumping);
	}
    noPressed = false;
}


PlayerJumpingState::~PlayerJumpingState()
{

}

void PlayerJumpingState::Update(float dt)
{
	this->mPlayerData->player->AddVy(acceleratorY);

	if (mPlayerData->player->GetVy() >= 0)

    {
		if (mPlayerData->player->mIsJumpKeyPressed)
		{
			mPlayerData->player->SetState(new PlayerJumping2State(this->mPlayerData));
		}
		else
		{
			mPlayerData->player->SetState(new PlayerFallingState(this->mPlayerData));

		}

        return;
    }

    if (noPressed)
    {
        if (mPlayerData->player->getMoveDirection() == Player::MoveToLeft)
        {
			//this->mPlayerData->player->SetVx(Define::PLAYER_MAX_RUNNING_SPEED);
			//player dang di chuyen sang ben trai      
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
			//player dang di chuyen sang phai   
            if (mPlayerData->player->GetVx() > 0)
            {
                this->mPlayerData->player->AddVx(-acceleratorX);

                if (mPlayerData->player->GetVx() < 0)
                    this->mPlayerData->player->SetVx(0);
            }
        }
    }
}

void PlayerJumpingState::HandleKeyboard(std::map<int, bool> keys)
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

PlayerState::StateName PlayerJumpingState::GetState()
{
    return PlayerState::Jumping;
}
void PlayerJumpingState::OnCollision(Entity::EntityTypes type, eDirection dir, float dt)
{
	switch (type)
	{
	case Entity::None:
		if (dir == eDirection::UP)
		{
			/*mPlayerData->player->AddPosition(D3DXVECTOR2(0, 2));*/
			this->mPlayerData->player->SetState(new PlayerFallingState(this->mPlayerData));
		}
		else if (dir == eDirection::RIGHT)
		{
			mPlayerData->player->AddPosition(D3DXVECTOR2(-2, 0));
		}
		else if (dir == eDirection::LEFT)
		{
			mPlayerData->player->AddPosition(D3DXVECTOR2(2, 0));
		}

		break;
	default:
		break;
	}
}