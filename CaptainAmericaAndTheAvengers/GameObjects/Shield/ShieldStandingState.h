#pragma once
#include "ShieldState.h"

class ShieldStandingState : public ShieldState
{
public:
	ShieldStandingState(ShieldData *playerData);
    ~ShieldStandingState();

    void Update(float dt);

    void HandleKeyboard(std::map<int, bool> keys);

    virtual StateName GetState();

protected:
};

