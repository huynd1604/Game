#pragma once
#include "PlayerState.h"

class PlayerSurfingState : public PlayerState
{
public:
    PlayerSurfingState(PlayerData *playerData);
    ~PlayerSurfingState();

    void Update(float dt);

    void HandleKeyboard(std::map<int, bool> keys);

    virtual StateName GetState();

protected:
};

