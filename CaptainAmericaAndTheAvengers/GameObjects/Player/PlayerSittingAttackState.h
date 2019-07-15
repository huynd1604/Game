#pragma once
#include "PlayerState.h"

class PlayerSittingAttackState : public PlayerState
{
public:
    PlayerSittingAttackState(PlayerData *playerData);
    ~PlayerSittingAttackState();

    void Update(float dt);

    void HandleKeyboard(std::map<int, bool> keys);

    virtual StateName GetState();

protected:
};

