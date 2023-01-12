#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "MatWorld.h"
#include "ViewProjection.h"
class stageMap
{

public:
	void Initialize();

	void Draw(ViewProjection viewProjection_);
public:
	static const int mapMax = 10;

private:
	WorldTransform worldTransform_[mapMax] = {};

	Model* modelWall_ = nullptr;

	MatWorld* matWorld_ = nullptr;
};

