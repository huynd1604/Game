#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include "../../GameComponents/Animation.h"
#include "../../GameComponents/GameGlobal.h"
#include "../../GameComponents/Camera.h"
#include "../../GameComponents/GameColision.h"
#include "../Entity.h"
#include "PlayerData.h"
#include "PlayerState.h"
#include "PlayerRunningState.h"
#include "../Shield/Shield.h"

class Player : public Entity
{
public:
	static Player*    instance;
	static Player *GetInstance();
    ~Player();

	Shield *mShield;
	enum MoveDirection
    {
        MoveToLeft, //chay tu phai sang trai
        MoveToRight, //chay tu trai sang phai
        None //dung im
    };

    void Update(float dt);

    void Draw(D3DXVECTOR3 position = D3DXVECTOR3(), RECT sourceRect = RECT(), D3DXVECTOR2 scale = D3DXVECTOR2(), D3DXVECTOR2 transform = D3DXVECTOR2(), float angle = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2(), D3DXCOLOR colorKey = D3DCOLOR_XRGB(255, 255, 255));

    void SetState(PlayerState *newState);

    MoveDirection getMoveDirection();

    RECT GetBound();     
	int GetAnimationIndex();
	bool IsLastAnimation();
	void SetPosition(float x, float y);
	void SetVx(float vx);
	void AddVx(float vx);
	void SetVy(float vy);
	void AddVy(float vy);
    PlayerState::StateName Player::getState();

    //xu ly input
    //gom 256 key tuong ung true = dang dc nhan, false = khong dc nhan
    void HandleKeyboard(std::map<int, bool> keys);

    void OnKeyPressed(int key);

    void OnKeyUp(int key);
	void OnColision(EntityTypes type, eDirection,float);
    //true thi se lat nguoc anh theo truc y
    void SetReverse(bool flag);
	bool mIsJumpKeyPressed;
	void SetCamera(Camera *camera);
	D3DXVECTOR3 GetShieldAdd();
	PlayerData *mPlayerData;
protected:
	Player();
	Camera      *mCamera;
	float mSx, mSy;
	Animation   *mCurrentAnimation,
				*mAnimationStanding,
				*mAnimationRunning,
				*mAnimationJumping,
				*mAnimationAttackNormal,
				*mAnimationSitting,
				*mAnimationAttackShield,
				*mAnimationSittingAttack,
				*mAnimationJumping2,
				*mAnimationTopDef,
				*mAnimationSurfing,
				*mAnimationSwim,
				*mAnimationButtomDef,
				*mAnimationSwing
		;

    void changeAnimation(PlayerState::StateName state);

    PlayerState::StateName mCurrentState;

    //chi cho phep jump khi nhan nhim space, muon nhay lai phai tha phim space roi nhan lai
    bool allowJump, mCurrentReverse;;
};

