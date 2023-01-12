#include "stageMap.h"

void stageMap::Initialize()
{
	modelWall_ = Model::CreateFromOBJ("wall");

	for (int i = 0; i < mapMax; i++)
	{
		worldTransform_[i].scale_ = { 0.5f,0.5f,0.5f };
		worldTransform_[i].translation_ = { i * 2.0f,0,0 };
		worldTransform_[i].Initialize();
		//?
		worldTransform_[i].matWorld_ = matWorld_->CreateMatWorld(worldTransform_[i]);
		//?
		worldTransform_[i].TransferMatrix();
	}
}

void stageMap::Draw(ViewProjection viewProjection_)
{
	for (int i = 0; i < mapMax; i++)
	{
		modelWall_->Draw(worldTransform_[i], viewProjection_);
	}
}