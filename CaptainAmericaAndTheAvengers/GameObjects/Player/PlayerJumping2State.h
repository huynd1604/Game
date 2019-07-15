#pragma once
#include "Player.h"
#include "PlayerState.h"

class PlayerJumping2State : public PlayerState
{
public:
    PlayerJumping2State(PlayerData *playerData);
    ~PlayerJumping2State();

    void Update(float dt);

    void HandleKeyboard(std::map<int, bool> keys);

    virtual StateName GetState();

protected:
    //do bien tien van toc sau moi frame tinh bang pixel / s
    float acceleratorY;
    float acceleratorX;
    bool noPressed;
    bool allowMoveRight, allowMoveLeft;
};

