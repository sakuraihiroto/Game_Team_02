#include "stageMap.h"



void stageMap::Initialize()
{
	modelWall_ = Model::CreateFromOBJ("wall");
	modelChain_ = Model::CreateFromOBJ("chain");
	modelHoll_ = Model::CreateFromOBJ("holl");
	modelFloor_ = Model::CreateFromOBJ("floor");

	// シングルトンインスタンスを取得する
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();


	for (int z = 0; z < mapMax; z++)
	{
		for (int x = 0; x < mapMax; x++)
		{

			//ステージ
			worldTransform_[z][x].scale_ = { 1.0f,1.0f,1.0f };
			worldTransform_[z][x].translation_ = { -7 + x * 2.0f, 0, 10 + z * -2.0f };
			worldTransform_[z][x].Initialize();

			worldTransform_[z][x].matWorld_ = matWorld_->CreateMatWorld(worldTransform_[z][x]);

			worldTransform_[z][x].TransferMatrix();

			//床
			worldTransformFloor_[z][x].scale_ = { 1.0f,1.0f,1.0f };
			worldTransformFloor_[z][x].translation_ = { -7 + x * 2.0f, -2, 10 + z * -2.0f };
			worldTransformFloor_[z][x].Initialize();

			worldTransformFloor_[z][x].matWorld_ = matWorld_->CreateMatWorld(worldTransformFloor_[z][x]);

			worldTransformFloor_[z][x].TransferMatrix();

			//壁
			worldTransformWall_[z][x].scale_ = { 1.0f,1.0f,1.0f };
			worldTransformWall_[z][x].translation_ = { -7 + x * 2.0f, 2, 10 + z * -2.0f };
			worldTransformWall_[z][x].Initialize();

			worldTransformWall_[z][x].matWorld_ = matWorld_->CreateMatWorld(worldTransformWall_[z][x]);

			worldTransformWall_[z][x].TransferMatrix();

			//天井
			worldTransformCeiling_[z][x].scale_ = { 1.0f,1.0f,1.0f };
			worldTransformCeiling_[z][x].translation_ = { -7 + x * 2.0f, 4, 10 + z * -2.0f };
			worldTransformCeiling_[z][x].Initialize();

			worldTransformCeiling_[z][x].matWorld_ = matWorld_->CreateMatWorld(worldTransformCeiling_[z][x]);

			worldTransformCeiling_[z][x].TransferMatrix();
		}
	}
}

void stageMap::Draw(ViewProjection viewProjection_)
{
	for (int z = 0; z < mapMax; z++)
	{
		for (int x = 0; x < mapMax; x++)
		{
			//ステージ
			if (mapData[z][x] == Block)
			{
				modelWall_->Draw(worldTransform_[z][x], viewProjection_);
			}

			//移動不可ブロック
			if (mapData[z][x] == BlockObj)
			{
				modelChain_->Draw(worldTransform_[z][x], viewProjection_);
			}

			//床
			if (floorData[z][x] == Floor)
			{
				modelFloor_->Draw(worldTransformFloor_[z][x], viewProjection_);
			}

			//落とし穴
			if (floorData[z][x] == Holl)
			{
				modelHoll_->Draw(worldTransformFloor_[z][x], viewProjection_);
			}
			//埋められた床
			if (floorData[z][x] == FilledFloor)
			{
				modelWall_->Draw(worldTransformFloor_[z][x], viewProjection_);
			}

			//壁
			if (wallData[z][x] == Block)
			{
				modelWall_->Draw(worldTransformWall_[z][x], viewProjection_);
			}

			/*modelWall_->Draw(worldTransformCeiling_[z][x], viewProjection_);*/
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

			if (mapData[z][x] == Block || mapData[z][x] == BlockObj)
			{

				position.x = worldTransform_[z][x].translation_.x;
				position.z = worldTransform_[z][x].translation_.z;



				float dx = abs(position.x - px);
				float dz = abs(position.z - pz);

				float tx1 = abs(position.x - px + 1);
				float tz1 = abs(position.z - pz + 1);

				float tx2 = abs(position.x - px - 1);
				float tz2 = abs(position.z - pz - 1);


				//壁を消す際の当たり判定
				if (tx1 < 1.5f && tz1 < 1.5f || tx2 < 1.5f && tz2 < 1.5f) {

					touchData[z][x] = 1;

				}
				else {
					touchData[z][x] = 0;
				}

				//プレイヤーとの当たり判定
				if (dx < 1.5f && dz < 1.5f)
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

			if (floorData[z][x] == Holl)
			{

				position.x = worldTransform_[z][x].translation_.x;
				position.z = worldTransform_[z][x].translation_.z;



				float dx = abs(position.x - px);
				float dz = abs(position.z - pz);

				//プレイヤーが来たら反応
				if (dx < 1.6f && dz < 1.6f)
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
			if (mapData[z][x] == Block)
			{
				position.x = worldTransform_[z][x].translation_.x;
				position.z = worldTransform_[z][x].translation_.z;



				float dx = abs(position.x - px);
				float dz = abs(position.z - pz);


				//判定が当たっていて消す判定もあり、他にブロックを持っていなければ
				if (dx < 2.0f && dz < 2.0f && touchData[z][x] == 1 && possFlag_ == 0)
				{
					if (countPossBlock_ > 0) {

						mapData[z][x] = none;
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



				if (dx < 3.0f && dz < 3.0f && floorData[z][x] == Holl)
				{
					floorData[z][x] = FilledFloor;
					possFlag_ = 0;
				}

			}
		}
	}
}

void stageMap::ResetStage()
{
	for (int z = 0; z < mapMax; z++)
	{

		for (int x = 0; x < mapMax; x++)
		{
			if (stage1Wall[z][x] == none)
			{
				mapData[z][x] = none;
			}
			else if (stage1Wall[z][x] == Block)
			{
				mapData[z][x] = Block;
			}
			else if (stage1Wall[z][x] == BlockObj)
			{
				mapData[z][x] = BlockObj;
			}


			if (stage1Floor[z][x] == Floor)
			{
				floorData[z][x] = Floor;
			}
			else if (stage1Floor[z][x] == Holl)
			{
				floorData[z][x] = Holl;
			}
		}
	}

	//取ったブロックを所持しているか
	possFlag_ = 0;

	//ブロックを取れる回数
	countPossBlock_ = 2;

}