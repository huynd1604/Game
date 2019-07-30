#pragma once
#include "PlayerData.h"
#include "../Entity.h"
#include "../../GameComponents/GameColision.h"
#include <map>

class PlayerState
{
public:
    enum StateName
    {
        Standing,
        Running,
        Falling,
        Jumping,
		TopDef,
		AttackShield,
		AttackNormal,
		AttackSitting,
		Sitting,
		Jumping2,
		Surfing,
		Swim,
		Swing,
		ButtomDef,
        Die
    };

    ~PlayerState();

    virtual void Update(float dt);

    virtual void HandleKeyboard(std::map<int, bool> keys);
	virtual void OnCollision(Entity::EntityTypes type, eDirection, float);
    //ham thuan ao bat buoc phai ke thua
    virtual StateName GetState() = 0;

protected:
    PlayerState(PlayerData *playerData);
    PlayerState();

    PlayerData *mPlayerData;
};

