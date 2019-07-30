#pragma once
#include "PlayerState.h"

class PlayerSwimState : public PlayerState
{
public:
    PlayerSwimState(PlayerData *playerData);
    ~PlayerSwimState();

    void Update(float dt);

    void HandleKeyboard(std::map<int, bool> keys);

    virtual StateName GetState();

protected:
};

