#include "Player.h"
#include "PlayerStandingState.h"
#include "PlayerJumpingState.h"
#include "PlayerTopDefState.h"
#include "PlayerAttackShield.h"
#include "PlayerSittingState.h"
#include "PlayerSittingAttackState.h"
#include "PlayerFallingState.h"
#include "PlayerAttackNormal.h"
#include "PlayerJumping2State.h"
#include "PlayerSurfingState.h"
#include "PlayerButtomDefState.h"
#include "PlayerSwingState.h"

Player* Player::instance = nullptr;

Player::Player()
{
	mAnimationStanding = new Animation("Resources/Captain/standing.png", 1, 1, 1, 0);
    mAnimationJumping = new Animation("Resources/Captain/jumping.png", 1, 1, 1, 0);
	mAnimationRunning = new Animation("Resources/Captain/run.png", 4, 1, 4, 0.15f);
	mAnimationTopDef = new Animation("Resources/Captain/def-top.png", 1, 1, 1, 0.0f);
	mAnimationAttackShield = new Animation("Resources/Captain/attack.png", 2, 1, 2, 0.15f);
	mAnimationAttackNormal = new Animation("Resources/Captain/normal-attack.png", 2, 1, 2, 0.15f);
	mAnimationSitting = new Animation("Resources/Captain/sitting.png", 1, 1, 1, 0.0f);
	mAnimationSittingAttack = new Animation("Resources/Captain/setting-attack.png", 2, 1, 2, 0.15f);
	mAnimationJumping2 = new Animation("Resources/Captain/jumping2.png", 2, 1, 2, 0.15f);
	mAnimationSurfing		 = new Animation("Resources/Captain/surfing.png", 3, 1, 3, 0.2f);
	mAnimationSwim		 = new Animation("Resources/Captain/swim.png", 2, 1, 2, 0.15f);
	mAnimationSwing		 = new Animation("Resources/Captain/swing.png", 3, 1, 3, 0.2f);
	mAnimationButtomDef = new Animation("Resources/Captain/buttom-def.png", 1, 1, 1, 0.0f);

	mIsJumpKeyPressed = false;
	mCurrentAnimation = NULL;
	this->mShield = new Shield();
    this->mPlayerData = new PlayerData();
    this->mPlayerData->player = this;
    this->vx = 0;
    this->vy = 0;
    this->SetState(new PlayerFallingState(this->mPlayerData));

    allowJump = true;
}

Player * Player::GetInstance()
{
	if (!instance)
		instance = new Player();
	return instance;
}

Player::~Player()
{
}

void Player::Update(float dt)
{    
    mCurrentAnimation->Update(dt);

    if (this->mPlayerData->state)
    {
        this->mPlayerData->state->Update(dt);
    }
	if (mShield->getState() != ShieldState::StateName::Attack)
	{
		mShield->SetPosition(D3DXVECTOR2(posX + (mCurrentReverse ? -mSx : mSx), posY + mSy));

	}
	else
	{
		if (abs(mShield->GetPosition().x - oldPosX) > 100.0f)
		{

			if (mShield->GetPosition().x > posX)
			{
				mShield->SetVx(-GameGlobal::Vshield);
			}
			else
			{
				mShield->SetVx(GameGlobal::Vshield);

			}
			
		}

		/*if (abs(mShield->GetPosition().y - posY)>30.0f)
		{
			if (mShield->GetPosition().y > posY + mSy)
			{
				mShield->SetVy(-GameGlobal::Vshield);
			}
			else if (mShield->GetPosition().y < posY + mSy)
			{
				mShield->SetVy(GameGlobal::Vshield);

			}
			else
			{
				mShield->SetVy(0);
			}
		}*/
	}
	
	mShield->Update(dt);
    Entity::Update(dt);
}

void Player::HandleKeyboard(std::map<int, bool> keys)
{
    if (this->mPlayerData->state)
    {
        this->mPlayerData->state->HandleKeyboard(keys);
    }
}

void Player::OnKeyPressed(int key)
{
    if (key == 'X')
    {
		mIsJumpKeyPressed = true;

        if (allowJump)
        {
            if (mCurrentState == PlayerState::Running || mCurrentState == PlayerState::Standing)
            {
                this->SetState(new PlayerJumpingState(this->mPlayerData));
            }
			else if (mCurrentState == PlayerState::Jumping)
			{
				this->SetState(new PlayerJumping2State(this->mPlayerData));
			}
            allowJump = false;
        }

    }
	else if (key == VK_UP)
	{
		if (mCurrentState == PlayerState::Running || mCurrentState == PlayerState::Standing)
		{
			this->SetState(new PlayerTopDefState(this->mPlayerData));
		}
	}
	else if (key == 'Z')
	{
		if (mCurrentState == PlayerState::Running || mCurrentState == PlayerState::Standing)
		{
			if (mShield->getState() == ShieldState::Attack)
			{
				this->SetState(new PlayerAttackNormal(this->mPlayerData));
			}
			else {
				this->SetState(new PlayerAttackShield(this->mPlayerData));
			}
		}
		else if (mCurrentState == PlayerState::Sitting)
		{
			this->SetState(new PlayerSittingAttackState(this->mPlayerData));
		}
		
		
	}
	else if (key == VK_DOWN)
	{
		if (mCurrentState == PlayerState::Running || mCurrentState == PlayerState::Standing)
		{
			this->SetState(new PlayerSittingState(this->mPlayerData));
		}
		else if (mCurrentState == PlayerState::Falling)
		{
			this->SetState(new PlayerButtomDefState(this->mPlayerData));
		}
	}
	else if (key == 'A')
	{
		
		this->SetState(new PlayerSurfingState(this->mPlayerData));
		
	}
	else if (key == 'S')
	{

		this->SetState(new PlayerSwingState(this->mPlayerData));

	}
}

void Player::OnKeyUp(int key)
{
	if (key == 'X')
	{
		allowJump = true;
		mIsJumpKeyPressed = false;

	}
	else if (key == VK_UP)
	{
		if (mCurrentState == PlayerState::TopDef)
		{
			this->SetState(new PlayerStandingState(this->mPlayerData));
		}
	}
	else if (key == VK_DOWN)
	{
		if (mCurrentState == PlayerState::AttackSitting || mCurrentState == PlayerState::Sitting)
		{
			this->SetState(new PlayerStandingState(this->mPlayerData));
		}
	}

}

void Player::OnColision(EntityTypes type, eDirection dir, float dt)
{
	this->mPlayerData->state->OnCollision(type, dir, dt);
}



void Player::SetReverse(bool flag)
{
    mCurrentReverse = flag;
	mShield->SetReverse(mCurrentReverse);
}

void Player::SetCamera(Camera *camera)
{
	this->mCamera = camera;
	mShield->SetCamera(camera);
}

D3DXVECTOR3 Player::GetShieldAdd()
{
	return D3DXVECTOR3((mCurrentReverse ? -mSx -15 : mSx + 15), mSy,0.0f);
}

void Player::Draw(D3DXVECTOR3 position, RECT sourceRect, D3DXVECTOR2 scale, D3DXVECTOR2 transform, float angle, D3DXVECTOR2 rotationCenter, D3DXCOLOR colorKey)
{
	mCurrentAnimation->FlipVertical(mCurrentReverse);
	mCurrentAnimation->SetPosition(this->GetPosition());

	if (mCamera)
	{
		D3DXVECTOR2 trans = D3DXVECTOR2(GameGlobal::GetWidth() / 2 - mCamera->GetPosition().x,
			GameGlobal::GetHeight() / 2 - mCamera->GetPosition().y);
		mCurrentAnimation->Draw(D3DXVECTOR3(posX, posY, 0), sourceRect, scale, trans, angle, rotationCenter, colorKey);
	}
	else
	{
		mCurrentAnimation->Draw(D3DXVECTOR3(posX, posY, 0));
	}
	mShield->Draw();
}

void Player::SetState(PlayerState *newState)
{
	if (mCurrentAnimation)
	{
		mCurrentAnimation->SetLastAnimation(false);
	}

	delete this->mPlayerData->state;

    this->mPlayerData->state = newState;

    this->changeAnimation(newState->GetState());

    mCurrentState = newState->GetState();
}

RECT Player::GetBound()
{
    RECT rect;
    rect.left = this->posX - mCurrentAnimation->GetWidth() / 2;
    rect.right = rect.left + mCurrentAnimation->GetWidth();
    rect.top = this->posY - mCurrentAnimation->GetHeight() / 2;
    rect.bottom = rect.top + mCurrentAnimation->GetHeight();

    return rect;
}

void Player::changeAnimation(PlayerState::StateName state)
{
    switch (state)
    {
        case PlayerState::Running:
            mCurrentAnimation = mAnimationRunning;
			mSx = 9.0f;
			mSy = -6.0f;
            break;

        case PlayerState::Standing:
			mSx = 9.0f;
			mSy = -5.0f;
            mCurrentAnimation = mAnimationStanding;
            break;

        case PlayerState::Falling:
            mCurrentAnimation = mAnimationJumping;
			mSx = -2.0f;
			mSy = -5.0f;
            break;

		case PlayerState::Jumping:
			mCurrentAnimation = mAnimationJumping;
			mSx = -2.0f;
			mSy = -5.0f;
			break;
		case PlayerState::TopDef:
			mCurrentAnimation = mAnimationTopDef;
			mSx = 1.0f;
			mSy = -18.0f;
			break;
		case PlayerState::AttackShield:
			mCurrentAnimation = mAnimationAttackShield;
			mSx = 15.0f;
			mSy = -3.0f;
			break;
		case PlayerState::AttackNormal:
			mCurrentAnimation = mAnimationAttackNormal;
			break;
		case PlayerState::AttackSitting:
			mCurrentAnimation = mAnimationSittingAttack;
			mSx = -2.0f;
			mSy = 10.0f;
			break;
		case PlayerState::Sitting:
			mSx = 4.0f;
			mSy = 12.0f;
			mCurrentAnimation = mAnimationSitting;
			break;
		case PlayerState::Jumping2:
			mCurrentAnimation = mAnimationJumping2;
			break;
		case PlayerState::ButtomDef:
			mCurrentAnimation = mAnimationButtomDef;
			break;
		case PlayerState::Swim:
			mCurrentAnimation = mAnimationSwim;
			break;
		case PlayerState::Swing:
			mCurrentAnimation = mAnimationSwing;
			break;
		case PlayerState::Surfing:
			mSx = 9.0f;
			mSy = -5.0f;
			mCurrentAnimation = mAnimationSurfing;
			break;
    }

    this->width = mCurrentAnimation->GetWidth();
    this->height = mCurrentAnimation->GetHeight();
}

Player::MoveDirection Player::getMoveDirection()
{
    if (this->vx > 0)
    {
        return MoveDirection::MoveToRight;
    }
    else if (this->vx < 0)
    {
        return MoveDirection::MoveToLeft;
    }

    return MoveDirection::None;
}

PlayerState::StateName Player::getState()
{
    return mCurrentState;
}

int Player::GetAnimationIndex()
{
	return mCurrentAnimation->GetAnimationIndex();
}
bool Player::IsLastAnimation()
{
	return mCurrentAnimation->GetLastAnimation();
}

void Player::SetPosition(float x, float y)
{
	Entity::SetPosition(D3DXVECTOR2(x, y));
}

void Player::SetVx(float vx)
{
	this->vx = vx;
}

void Player::AddVx(float vx)
{
	this->vx += vx;
}


void Player::SetVy(float vy)
{
	this->vy = vy;
}

void Player::AddVy(float vy)
{
	this->vy += vy;
}
