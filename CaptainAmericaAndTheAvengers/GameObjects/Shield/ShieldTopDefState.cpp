#include "ShieldTopDefState.h"
#include "Shield.h"
#include "../../GameDefines/GameDefine.h"

ShieldTopDefState::ShieldTopDefState(ShieldData *playerData)
{
	this->mShieldData = playerData;
}


ShieldTopDefState::~ShieldTopDefState()
{
}

void ShieldTopDefState::Update(float dt)
{
//	this->mShieldData->shield->AddPosition(this->mShieldData->shield->GetPosition() + D3DXVECTOR3(10, 3, 0));
}

void ShieldTopDefState::HandleKeyboard(std::map<int, bool> keys)
{

	
}

ShieldState::StateName ShieldTopDefState::GetState()
{
    return StateName::TopDef;
}
