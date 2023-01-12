#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "MatWorld.h"
#include "ViewProjection.h"
#include <DirectXMath.h>
#include "DebugText.h"

using namespace DirectX;


class stageMap
{

public:
	void Initialize();

	void Draw(ViewProjection viewProjection_);

	bool Collision(float px, float pz);

	bool CollisionHoll(float px, float pz);

	void DeleteBlock(float px, float pz);



public:
	static const int mapMax = 10;

private:
	WorldTransform worldTransform_[mapMax][mapMax] = {};
	WorldTransform worldTransformTile_[mapMax][mapMax] = {};

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

	Model* modelWall_ = nullptr;

	MatWorld* matWorld_ = nullptr;

	// デバッグテキスト
	DebugText* debugText_ = nullptr;

};

