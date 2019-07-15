#pragma once
#include "PlayerState.h"

class PlayerTopDefState : public PlayerState
{
public:
    PlayerTopDefState(PlayerData *playerData);
    ~PlayerTopDefState();

    void Update(float dt);

    void HandleKeyboard(std::map<int, bool> keys);

    virtual StateName GetState();

protected:
};

