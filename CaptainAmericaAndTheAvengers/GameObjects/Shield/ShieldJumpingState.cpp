#include "ShieldJumpingState.h"
#include "Shield.h"
#include "../../GameDefines/GameDefine.h"

ShieldJumpingState::ShieldJumpingState(ShieldData *playerData)
{
	this->mShieldData = playerData;
}


ShieldJumpingState::~ShieldJumpingState()
{
}

void ShieldJumpingState::Update(float dt)
{
//	this->mShieldData->shield->AddPosition(this->mShieldData->shield->GetPosition() + D3DXVECTOR3(10, 3, 0));
}

void ShieldJumpingState::HandleKeyboard(std::map<int, bool> keys)
{

	
}

ShieldState::StateName ShieldJumpingState::GetState()
{
    return StateName::Jumping;
}
