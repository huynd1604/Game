#pragma once
#include "PlayerState.h"

class PlayerSwingState : public PlayerState
{
public:
    PlayerSwingState(PlayerData *playerData);
    ~PlayerSwingState();

    void Update(float dt);

    void HandleKeyboard(std::map<int, bool> keys);

    virtual StateName GetState();

protected:
};

