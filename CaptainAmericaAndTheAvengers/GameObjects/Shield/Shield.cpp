#include "Shield.h"
#include "ShieldStandingState.h"
#include "ShieldRunningState.h"
#include "ShieldJumpingState.h"
#include "ShieldTopDefState.h"
#include "ShieldAttackState.h"

Shield::Shield()
{
	mAnimationStanding = new Animation("Resources/Captain/shield/standing.png", 1, 1, 1, 0);
	mAnimationJumping = new Animation("Resources/Captain/shield/jumping.png", 1, 1, 1, 0);
	mAnimationRunning = new Animation("Resources/Captain/shield/run.png", 4, 1, 4, 0.15f);
	mAnimationTopDef = new Animation("Resources/Captain/shield/top-def.png", 1, 1, 1, 0);
	mAnimationAttack = new Animation("Resources/Captain/shield/top-def.png", 1, 1, 1, 0);
   
	mIsJumpKeyPressed = false;
	mCurrentAnimation = NULL;
    this->mShieldData = new ShieldData();
    this->mShieldData->shield = this;
    this->vx = 0;
    this->vy = 0;
    this->SetState(new ShieldStandingState(this->mShieldData));

    allowJump = true;
}

Shield::~Shield()
{
}

void Shield::Update(float dt)
{    
	if (mCurrentState != ShieldState::StateName::Jumping2)
	{
		mCurrentAnimation->Update(dt);

		if (this->mShieldData->state)
		{
			this->mShieldData->state->Update(dt);
		}

		Entity::Update(dt);
	}
}

void Shield::HandleKeyboard(std::map<int, bool> keys)
{
    if (this->mShieldData->state)
    {
        this->mShieldData->state->HandleKeyboard(keys);
    }
}

void Shield::OnKeyPressed(int key)
{
}

void Shield::OnKeyUp(int key)
{
	
}

void Shield::SetReverse(bool flag)
{
    mCurrentReverse = flag;
}

bool Shield::GetReverse()
{
	return mCurrentReverse;
}

void Shield::SetCamera(Camera *camera)
{
	this->mCamera = camera;
}

bool Shield::IsNeedCheck()
{
	return mCurrentState != ShieldState::StateName::Jumping2;
}

void Shield::Draw(D3DXVECTOR3 position, RECT sourceRect, D3DXVECTOR2 scale, D3DXVECTOR2 transform, float angle, D3DXVECTOR2 rotationCenter, D3DXCOLOR colorKey)
{
	if (mCurrentState != ShieldState::StateName::Jumping2)
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
	}

}

void Shield::SetState(ShieldState *newState)
{
	if (mCurrentAnimation)
	{
		mCurrentAnimation->SetLastAnimation(false);
	}

	delete this->mShieldData->state;

    this->mShieldData->state = newState;

    this->changeAnimation(newState->GetState());

    mCurrentState = newState->GetState();
}
void Shield::SetState(ShieldState::StateName newState)
{
	switch(newState)
	{
		case ShieldState::Standing:
			this->SetState(new ShieldStandingState(this->mShieldData));
			break;
		case ShieldState::Running:
			this->SetState(new ShieldRunningState(this->mShieldData));
			break;
		case ShieldState::Jumping:
			this->SetState(new ShieldJumpingState(this->mShieldData));
			break;
		case ShieldState::TopDef:
			this->SetState(new ShieldTopDefState(this->mShieldData));
			break;
		case ShieldState::Attack:
			this->SetState(new ShieldAttackState(this->mShieldData));
			break;
		case ShieldState::Jumping2:
			mCurrentState = ShieldState::Jumping2;
			break;
	}
}
RECT Shield::GetBound()
{
    RECT rect;
    rect.left = this->posX - mCurrentAnimation->GetWidth() / 2;
    rect.right = rect.left + mCurrentAnimation->GetWidth();
    rect.top = this->posY - mCurrentAnimation->GetHeight() / 2;
    rect.bottom = rect.top + mCurrentAnimation->GetHeight();

    return rect;
}

void Shield::changeAnimation(ShieldState::StateName state)
{
	switch (state)
	{
		case ShieldState::Standing:
			mCurrentAnimation = mAnimationStanding;
			break;
		case ShieldState::Running:
			mCurrentAnimation = mAnimationRunning;
			break;
		case ShieldState::Jumping:
			mCurrentAnimation = mAnimationJumping;
			break;
		case ShieldState::TopDef:
			mCurrentAnimation = mAnimationTopDef;
		case ShieldState::Attack:
			mCurrentAnimation = mAnimationAttack;
			break;
	}


    this->width = mCurrentAnimation->GetWidth();
    this->height = mCurrentAnimation->GetHeight();
}

Shield::MoveDirection Shield::getMoveDirection()
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

ShieldState::StateName Shield::getState()
{
    return mCurrentState;
}

int Shield::GetAnimationIndex()
{
	return mCurrentAnimation->GetAnimationIndex();
}
bool Shield::IsLastAnimation()
{
	return mCurrentAnimation->GetLastAnimation();
}