#include "ShieldRunningState.h"
#include "Shield.h"
#include "../../GameDefines/GameDefine.h"

ShieldRunningState::ShieldRunningState(ShieldData *playerData)
{
	this->mShieldData = playerData;
}


ShieldRunningState::~ShieldRunningState()
{
}

void ShieldRunningState::Update(float dt)
{
//	this->mShieldData->shield->AddPosition(this->mShieldData->shield->GetPosition() + D3DXVECTOR3(10, 3, 0));
}

void ShieldRunningState::HandleKeyboard(std::map<int, bool> keys)
{

	
}

ShieldState::StateName ShieldRunningState::GetState()
{
    return StateName::Running;
}
