#pragma once
#include "PlayerState.h"
#include "Player.h"

class PlayerRunningState : public PlayerState
{
public:
    PlayerRunningState(PlayerData *playerData);
    ~PlayerRunningState();

    void Update(float dt);

    void HandleKeyboard(std::map<int, bool> keys);
	void OnCollision(Entity::EntityTypes type, eDirection, float);

    virtual StateName GetState();

protected:
    //do bien tien van toc sau moi frame tinh bang pixel / s
    float acceleratorX;
};

