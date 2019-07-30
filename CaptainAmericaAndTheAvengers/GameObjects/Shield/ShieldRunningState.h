#pragma once
#include "ShieldState.h"

class ShieldRunningState : public ShieldState
{
public:
	ShieldRunningState(ShieldData *playerData);
    ~ShieldRunningState();

    void Update(float dt);

    void HandleKeyboard(std::map<int, bool> keys);

    virtual StateName GetState();

protected:
};

