#pragma once

#include <d3dx9.h>
#include <d3d9.h>

#include "../GameComponents/GameGlobal.h"

class Entity
{

public:

    Entity();


    enum EntityTypes
    {
        None
    };

    EntityTypes Tag; //Tag de nhan dien loai Entity

    virtual RECT GetBound();

    virtual void SetPosition(float x, float y);

    virtual void SetPosition(D3DXVECTOR2 pos);

    virtual void SetPosition(D3DXVECTOR3 pos);

    virtual void AddPosition(D3DXVECTOR3 pos);

    virtual void AddPosition(D3DXVECTOR2 pos);

    virtual void AddPosition(float x, float y);

    virtual void SetWidth(int width);

    virtual int GetWidth();

    virtual void SetHeight(int height);

    virtual int GetHeight();

    virtual float GetVx();

    virtual void SetVx(float vx);

    virtual void AddVx(float vx);

    virtual float GetVy();

    virtual void SetVy(float vy);

    virtual void AddVy(float vy);

    virtual D3DXVECTOR3 GetPosition();

    virtual void Update(float dt);

	virtual float GetOldPosX();

	virtual float GetOldPosY();

	virtual void SetOldPosition(D3DXVECTOR3 pos);
protected:

    //duoc goi khi set position cua Entity, dung cho ke thua
    virtual void OnSetPosition(D3DXVECTOR3 pos);

    //vi tri tam position x va y
	float posX, posY;
	float oldPosX, oldPosY;

    //phan toc vx, vy
    float vx, vy;

    //size cua entity
    float width, height;
};