#include "stageMap.h"

void stageMap::Initialize()
{
	modelWall_ = Model::CreateFromOBJ("wall");

	for (int y = 0; y < mapMax; y++)
	{
		for (int x = 0; x < mapMax; x++)
		{
			worldTransform_[y][x].scale_ = { 0.5f,0.5f,0.5f };
			worldTransform_[y][x].translation_ = { x * 2.5f, 10 + y * -2.5f,0 };
			worldTransform_[y][x].Initialize();
			//çsóÒÇÃåvéZ
			worldTransform_[y][x].matWorld_ = matWorld_->CreateMatWorld(worldTransform_[y][x]);
			//çsóÒÇÃì]ëó
			worldTransform_[y][x].TransferMatrix();
		}
	}
}

void stageMap::Draw(ViewProjection viewProjection_)
{
	for (int y = 0; y < mapMax; y++)
	{
		for (int x = 0; x < mapMax; x++)
		{
			if (mapData[y][x] == 1)
			{
				modelWall_->Draw(worldTransform_[y][x], viewProjection_);
			}
		}
	}
}
