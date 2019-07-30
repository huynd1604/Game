#pragma once
#include "PlayerState.h"

class PlayerButtomDefState : public PlayerState
{
public:
    PlayerButtomDefState(PlayerData *playerData);
    ~PlayerButtomDefState();

    void Update(float dt);

    void HandleKeyboard(std::map<int, bool> keys);

    virtual StateName GetState();

protected:
};

