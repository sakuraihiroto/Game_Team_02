#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "MatWorld.h"
#include "ViewProjection.h"
#include <DirectXMath.h>
#include "DebugText.h"
#include "Input.h"

using namespace DirectX;


class stageMap
{

public:
	void Initialize();

	void Draw(ViewProjection viewProjection_);

	bool Collision(float px, float pz);

	bool CollisionHoll(float px, float pz);

	void DeleteBlock(float px, float pz);

	void ResetMap();

	void PutBlock(float px, float pz);

public:
	static const int mapMax = 10;

private:

	WorldTransform worldTransform_[mapMax][mapMax] = {};
	WorldTransform worldTransformTile_[mapMax][mapMax] = {};

	int mapData[mapMax][mapMax] = {
		{2,1,1,1,1,1,1,1,1,2},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,1,1,1,0,1,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,1,1,1,1,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,1,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,1,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{2,1,1,1,1,1,1,1,1,2}
	};

	int TileData[mapMax][mapMax] = {
		{1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1},
		{1,1,1,2,1,2,1,1,1,1},
		{1,1,1,2,1,2,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1}
	};

	int touchData[mapMax][mapMax] = {
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0}
	};

	Model* modelWall_ = nullptr;

	MatWorld* matWorld_ = nullptr;

	// �f�o�b�N�e�L�X�g
	DebugText* debugText_ = nullptr;

	// ���͏������邽��
	Input* input_ = nullptr;

	//������u���b�N���������Ă��邩
	int possFlag_ = 0;

	//�u���b�N�������
	int countPossBlock_ = 2;

};