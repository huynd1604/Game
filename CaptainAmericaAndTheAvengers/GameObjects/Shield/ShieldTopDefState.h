#pragma once
#include "ShieldState.h"

class ShieldTopDefState : public ShieldState
{
public:
	ShieldTopDefState(ShieldData *playerData);
    ~ShieldTopDefState();

    void Update(float dt);

    void HandleKeyboard(std::map<int, bool> keys);

    virtual StateName GetState();

protected:
};

