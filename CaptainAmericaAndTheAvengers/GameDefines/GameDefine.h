#pragma once
#define TEXTURE LPDIRECT3DTEXTURE9
namespace Define
{
    const float PLAYER_MAX_JUMP_VELOCITY = 180.0f; //van toc nhay lon nhat
    const float PLAYER_MIN_JUMP_VELOCITY = -180.0f; //van toc nhay thap nhat
	const float PLAYER_MAX_RUNNING_SPEED = 70.0f; //toc do chay nhanh nhat cua player
	const float SHIELD_MAX_RUNNING_SPEED = 180.0f; //toc do chay nhanh nhat cua player
    const float PLAYER_BOTTOM_RANGE_FALLING = 8.0f; // do dai va cham voi bottom neu nhu va cham bottom nho hon thi player se bi roi xuong
	const int GRID_WIDTH = 96;
	const int GRID_HEIGHT = 96;
}
