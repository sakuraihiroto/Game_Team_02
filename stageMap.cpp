#include "stageMap.h"



void stageMap::Initialize()
{
	modelWall_ = Model::CreateFromOBJ("proto");

	// シングルトンインスタンスを取得する
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();

	for (int z = 0; z < mapMax; z++)
	{
		for (int x = 0; x < mapMax; x++)
		{
			worldTransform_[z][x].scale_ = { 1.0f,1.0f,1.0f };
			worldTransform_[z][x].translation_ = { -7 + x * 2.0f, 0, 10 + z * -2.0f };
			worldTransform_[z][x].Initialize();
			//行列の計算
			worldTransform_[z][x].matWorld_ = matWorld_->CreateMatWorld(worldTransform_[z][x]);
			//行列の転送
			worldTransform_[z][x].TransferMatrix();

			worldTransformTile_[z][x].scale_ = { 1.0f,1.0f,1.0f };
			worldTransformTile_[z][x].translation_ = { -7 + x * 2.0f, -2, 10 + z * -2.0f };
			worldTransformTile_[z][x].Initialize();
			//行列の計算	  
			worldTransformTile_[z][x].matWorld_ = matWorld_->CreateMatWorld(worldTransformTile_[z][x]);
			//行列の転送	  
			worldTransformTile_[z][x].TransferMatrix();
		}
	}
}

void stageMap::Draw(ViewProjection viewProjection_)
{
	for (int z = 0; z < mapMax; z++)
	{
		for (int x = 0; x < mapMax; x++)
		{
			if (mapData[z][x] == 1 || mapData[z][x] == 2)
			{
				modelWall_->Draw(worldTransform_[z][x], viewProjection_);
			}

			if (TileData[z][x] == 1)
			{
				modelWall_->Draw(worldTransformTile_[z][x], viewProjection_);
			}


		}
	}
}

bool stageMap::Collision(float px, float pz)
{
	Vector3 position;
	for (int z = 0; z < mapMax; z++)
	{

		for (int x = 0; x < mapMax; x++)
		{

			if (mapData[z][x] == 1 || mapData[z][x] == 2)
			{

				position.x = worldTransform_[z][x].translation_.x;
				position.z = worldTransform_[z][x].translation_.z;



				float dx = abs(position.x - px);
				float dz = abs(position.z - pz);

				float tx1 = abs(position.x - px + 1);
				float tz1 = abs(position.z - pz + 1);

				float tx2 = abs(position.x - px - 1);
				float tz2 = abs(position.z - pz - 1);


				if (tx1 < 1.15f && tz1 < 1.15f || tx2 < 1.15f && tz2 < 1.15f) {

					touchData[z][x] = 1;

				}
				else {
					touchData[z][x] = 0;
				}

				if (dx < 1.8f && dz < 1.8f)
				{
					return true;
				}

			}
		}
	}
	return false;
}

bool stageMap::CollisionHoll(float px, float pz)
{
	Vector3 position;
	for (int z = 0; z < mapMax; z++)
	{

		for (int x = 0; x < mapMax; x++)
		{

			if (TileData[z][x] == 2)
			{

				position.x = worldTransform_[z][x].translation_.x;
				position.z = worldTransform_[z][x].translation_.z;



				float dx = abs(position.x - px);
				float dz = abs(position.z - pz);

				if (dx < 1.8f && dz < 1.8f)
				{
					return true;
				}
			}
		}
	}
	return false;
}

void stageMap::DeleteBlock(float px, float pz)
{
	Vector3 position;
	Vector3 position2;
	for (int z = 0; z < mapMax; z++)
	{

		for (int x = 0; x < mapMax; x++)
		{
			if (mapData[z][x] == 1)
			{
				position.x = worldTransform_[z][x].translation_.x;
				position.z = worldTransform_[z][x].translation_.z;



				float dx = abs(position.x - px);
				float dz = abs(position.z - pz);



				if (dx < 2.0f && dz < 2.0f && touchData[z][x] == 1 && possFlag_ == 0)
				{
					if (countPossBlock_ > 0) {

						mapData[z][x] = 0;
						possFlag_ = 1;
						countPossBlock_--;
					}

				}
			}
		}
	}
}

void stageMap::PutBlock(float px, float pz)
{
	Vector3 position;

	for (int z = 0; z < mapMax; z++)
	{

		for (int x = 0; x < mapMax; x++)
		{
			if (possFlag_ == 1)
			{
				position.x = worldTransform_[z][x].translation_.x;
				position.z = worldTransform_[z][x].translation_.z;



				float dx = abs(position.x - px);
				float dz = abs(position.z - pz);



				if (dx < 3.0f && dz < 3.0f && TileData[z][x] == 2)
				{
					TileData[z][x] = 1;
					possFlag_ = 0;
				}

			}
		}
	}
}

void stageMap::ResetMap()
{
	possFlag_ = 0;
	countPossBlock_ = 2;


}