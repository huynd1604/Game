#pragma once
#include "PlayerState.h"

class PlayerAttackShield : public PlayerState
{
public:
    PlayerAttackShield(PlayerData *playerData);
    ~PlayerAttackShield();

    void Update(float dt);

    void HandleKeyboard(std::map<int, bool> keys);

    virtual StateName GetState();

protected:
};

