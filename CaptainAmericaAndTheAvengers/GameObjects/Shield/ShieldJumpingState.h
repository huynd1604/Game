#pragma once
#include "ShieldState.h"

class ShieldJumpingState : public ShieldState
{
public:
	ShieldJumpingState(ShieldData *playerData);
    ~ShieldJumpingState();

    void Update(float dt);

    void HandleKeyboard(std::map<int, bool> keys);

    virtual StateName GetState();

protected:
};

