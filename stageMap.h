#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "MatWorld.h"
#include "ViewProjection.h"
#include <DirectXMath.h>


using namespace DirectX;


class stageMap
{

public:
	void Initialize();

	void Draw(ViewProjection viewProjection_);

	bool Collision(float px, float pz);

	Vector3 GetWorldPosition();

public:
	static const int mapMax = 10;

private:
	WorldTransform worldTransform_[mapMax][mapMax] = {};

	int mapData[mapMax][mapMax] = {
		{1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,1,1,1,0,1,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,1,1,1,1,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,1,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,1,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1}
	};

	Model* modelWall_ = nullptr;

	MatWorld* matWorld_ = nullptr;
};

