#include "ShieldStandingState.h"
#include "Shield.h"
#include "../../GameDefines/GameDefine.h"

ShieldStandingState::ShieldStandingState(ShieldData *playerData)
{
	this->mShieldData = playerData;
	this->mShieldData->shield->SetVx(0);
	this->mShieldData->shield->SetVy(0);
}


ShieldStandingState::~ShieldStandingState()
{
}

void ShieldStandingState::Update(float dt)
{

}

void ShieldStandingState::HandleKeyboard(std::map<int, bool> keys)
{

	
}

ShieldState::StateName ShieldStandingState::GetState()
{
    return StateName::Standing;
}
