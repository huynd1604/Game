#include "ShieldAttackState.h"
#include "Shield.h"
#include "../../GameDefines/GameDefine.h"
#include "../Player/Player.h"

ShieldAttackState::ShieldAttackState(ShieldData *playerData)
{
	this->mShieldData = playerData;
	acceleratorX = 8.0f;
	this->mShieldData->shield->SetVx(mShieldData->shield->GetReverse() ? -GameGlobal::Vshield : GameGlobal::Vshield);
	this->mShieldData->shield->SetVy(0);
}


ShieldAttackState::~ShieldAttackState()
{
}

void ShieldAttackState::Update(float dt)
{
	float playerPosY = Player::GetInstance()->GetPosition().y;
	float playerPosX = Player::GetInstance()->GetPosition().x;
	float vy = (fabs(playerPosY - mShieldData->shield->GetPosition().y)*GameGlobal::Vshield*dt) / fabs(playerPosX - mShieldData->shield->GetPosition().x);
	if (mShieldData->shield->GetPosition().y > playerPosY)
	{
		vy = -vy;
	}
	/*else 
	{
		mShield->SetVy(GameGlobal::Vshield);

	}*/
	mShieldData->shield->SetPosition(mShieldData->shield->GetPosition() + D3DXVECTOR3(0, vy, 0));
	if (GameGlobal::isCollide(mShieldData->shield->GetBound(), Player::GetInstance()->GetBound()))
	{
		this->mShieldData->shield->SetVx(0);
		
		switch (Player::GetInstance()->getState())
		{
		case PlayerState::Running:
			mShieldData->shield->SetState(StateName::Running);
			break;

		case PlayerState::Standing:
			mShieldData->shield->SetState(StateName::Standing);
			break;

		case PlayerState::Falling:
			mShieldData->shield->SetState(StateName::Jumping);
			break;

		case PlayerState::Jumping:
			mShieldData->shield->SetState(StateName::Jumping);
			break;
		case PlayerState::TopDef:
			mShieldData->shield->SetState(StateName::TopDef);
			break;
		case PlayerState::AttackNormal:
			mShieldData->shield->SetState(StateName::Jumping2);
			break;
		case PlayerState::AttackSitting:
			mShieldData->shield->SetState(StateName::AttackSitting);
			break;
		case PlayerState::Sitting:
			mShieldData->shield->SetState(StateName::Standing);
			break;
		case PlayerState::Jumping2:
			mShieldData->shield->SetState(StateName::Jumping2);
			break;
		}
	}
}

void ShieldAttackState::HandleKeyboard(std::map<int, bool> keys)
{

	
}

ShieldState::StateName ShieldAttackState::GetState()
{
    return StateName::Attack;
}
