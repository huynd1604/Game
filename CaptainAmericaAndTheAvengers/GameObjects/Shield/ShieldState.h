#pragma once
#include "ShieldData.h"
#include "../Entity.h"
#include <map>

class ShieldState
{
public:
    enum StateName
    {
        Standing,
        Die
    };

    ~ShieldState();

    virtual void Update(float dt);

    virtual void HandleKeyboard(std::map<int, bool> keys);

    //ham thuan ao bat buoc phai ke thua
    virtual StateName GetState() = 0;

protected:
    ShieldState(ShieldData *shieldData);
    ShieldState();

    ShieldData *mShieldData;
};

