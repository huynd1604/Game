#pragma once
#include "ShieldState.h"

class ShieldAttackState : public ShieldState
{
public:
	ShieldAttackState(ShieldData *playerData);
    ~ShieldAttackState();

    void Update(float dt);

    void HandleKeyboard(std::map<int, bool> keys);

    virtual StateName GetState();

protected:
    float acceleratorX;
};

