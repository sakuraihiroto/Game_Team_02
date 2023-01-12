#include "stageMap.h"



void stageMap::Initialize()
{
	modelWall_ = Model::CreateFromOBJ("wall");

	for (int y = 0; y < mapMax; y++)
	{
		for (int x = 0; x < mapMax; x++)
		{
			worldTransform_[y][x].scale_ = { 0.5f,0.5f,0.5f };
			worldTransform_[y][x].translation_ = { -7 + x * 2.0f, 10 + y * -2.0f,0 };
			worldTransform_[y][x].Initialize();
			//行列の計算
			worldTransform_[y][x].matWorld_ = matWorld_->CreateMatWorld(worldTransform_[y][x]);
			//行列の転送
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

Vector3 stageMap::GetWorldPosition()
{
	//ワールド座標を入れる変数
	Vector3 worldPos;
	for (int y = 0; y < mapMax; y++)
	{
		for (int x = 0; x < mapMax; x++)
		{

			worldPos.x = worldTransform_[3][x].matWorld_.m[3][0];
		}
		worldPos.y = worldTransform_[3][y].matWorld_.m[3][1];
	}

	return worldPos;

}

bool stageMap::Collision(float px, float py)
{
	Vector3 position;
	for (int y = 0; y < mapMax; y++)
	{
		
		for (int x = 0; x < mapMax; x++)
		{
			
			if (mapData[y][x] == 1)
			{

				position.x = worldTransform_[y][x].translation_.x;
				position.y = worldTransform_[y][x].translation_.y;

				position.y += 1;

				float dx = abs(position.x - px);
				float dy = abs(position.y - py);

				if (dx < 1.8f && dy < 1.8f)
				{
					return true;
				}
			}
		}
	}
	return false;
}
