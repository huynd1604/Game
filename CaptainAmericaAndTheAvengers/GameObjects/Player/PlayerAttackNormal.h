#pragma once
#include "PlayerState.h"

class PlayerAttackNormal : public PlayerState
{
public:
    PlayerAttackNormal(PlayerData *playerData);
    ~PlayerAttackNormal();

    void Update(float dt);

    void HandleKeyboard(std::map<int, bool> keys);

    virtual StateName GetState();

protected:
};

