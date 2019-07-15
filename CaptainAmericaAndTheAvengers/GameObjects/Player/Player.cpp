#include "Player.h"
#include "PlayerStandingState.h"
#include "PlayerJumpingState.h"
#include "PlayerTopDefState.h"
#include "PlayerAttackShield.h"
#include "PlayerSittingState.h"
#include "PlayerSittingAttackState.h"
#include "PlayerFallingState.h"
#include "PlayerAttackNormal.h"

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
	mIsJumpKeyPressed = false;
	mCurrentAnimation = NULL;
	this->mShield = new Shield();
	
    this->mPlayerData = new PlayerData();
    this->mPlayerData->player = this;
    this->vx = 0;
    this->vy = 0;
    this->SetState(new PlayerStandingState(this->mPlayerData));

    allowJump = true;
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
    if (key == VK_SPACE)
    {
		mIsJumpKeyPressed = true;

        if (allowJump)
        {
            if (mCurrentState == PlayerState::Running || mCurrentState == PlayerState::Standing)
            {
                this->SetState(new PlayerJumpingState(this->mPlayerData));
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
			this->SetState(new PlayerAttackShield(this->mPlayerData));
		}
		else if (mCurrentState == PlayerState::Sitting)
		{
			this->SetState(new PlayerSittingAttackState(this->mPlayerData));
		}
	}
	else if (key == 'A')
	{
		if (mCurrentState == PlayerState::Running || mCurrentState == PlayerState::Standing)
		{
			this->SetState(new PlayerAttackNormal(this->mPlayerData));
		}
	}
	else if (key == VK_DOWN)
	{
		if (mCurrentState == PlayerState::Running || mCurrentState == PlayerState::Standing)
		{
			this->SetState(new PlayerSittingState(this->mPlayerData));
		}
	}
}

void Player::OnKeyUp(int key)
{
	if (key == VK_SPACE)
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
            break;

        case PlayerState::Standing:
            mCurrentAnimation = mAnimationStanding;
            break;

        case PlayerState::Falling:
            mCurrentAnimation = mAnimationJumping;
            break;

		case PlayerState::Jumping:
			mCurrentAnimation = mAnimationJumping;
			break;
		case PlayerState::TopDef:
			mCurrentAnimation = mAnimationTopDef;
			break;
		case PlayerState::AttackShield:
			mCurrentAnimation = mAnimationAttackShield;
			break;
		case PlayerState::AttackNormal:
			mCurrentAnimation = mAnimationAttackNormal;
			break;
		case PlayerState::AttackSitting:
			mCurrentAnimation = mAnimationSittingAttack;
			break;
		case PlayerState::Sitting:
			mCurrentAnimation = mAnimationSitting;
			break;
		case PlayerState::Jumping2:
			mCurrentAnimation = mAnimationJumping2;
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

