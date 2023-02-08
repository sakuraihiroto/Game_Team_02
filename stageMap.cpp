#include "stageMap.h"


int stageMap::iswhereStage_ = 0;

void stageMap::Initialize()
{
	modelWall_ = Model::CreateFromOBJ("wall");
	modelChain_ = Model::CreateFromOBJ("chain");
	modelHoll_ = Model::CreateFromOBJ("holl");
	modelFloor_ = Model::CreateFromOBJ("floor");
	modelGoal_ = Model::CreateFromOBJ("door");

	//プレイヤーの手(ブロック持ってないとき)
	textureHandle_hand_ = TextureManager::Load("hand.png");
	sprite_hand = Sprite::Create(textureHandle_hand_, { 700,350 });

	//プレイヤーの手(ブロック持ってるとき)
	textureHandle_handBox_ = TextureManager::Load("handbox.png");
	sprite_handBox = Sprite::Create(textureHandle_handBox_, { 700,350 });

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

void stageMap::Update() {

	if (pauseFlag_ == 0)
	{
		//ゴールしたらステージのフラグを進めてステージ更新
		if (isTouchedGoal == 1)
		{
			iswhereStage_++;
			isCreateStage_ = 1;
			isTouchedGoal = 0;
		}

		for (int z = 0; z < mapMax; z++)
		{
			//
			for (int x = 0; x < mapMax; x++)
			{
				if (isCreateStage_ == 1 && iswhereStage_ == tutorial)
				{
					if (tutoStageData[z][x] == none)
					{
						mapData[z][x] = none;
					}
					else if (tutoStageData[z][x] == Block)
					{
						mapData[z][x] = Block;
					}
					else if (tutoStageData[z][x] == BlockObj)
					{
						mapData[z][x] = BlockObj;
					}
					else if (tutoStageData[z][x] == Goal)
					{
						mapData[z][x] = Goal;
					}

					if (tutoFloorData[z][x] == Floor)
					{
						floorData[z][x] = Floor;
					}
					else if (tutoFloorData[z][x] == Holl)
					{
						floorData[z][x] = Holl;
					}
				}
				//
				else if (isCreateStage_ == 1 && iswhereStage_ == stage1)
				{
					if (stage1WallData[z][x] == none)
					{
						mapData[z][x] = none;
					}
					else if (stage1WallData[z][x] == Block)
					{
						mapData[z][x] = Block;
					}
					else if (stage1WallData[z][x] == BlockObj)
					{
						mapData[z][x] = BlockObj;
					}
					else if (stage1WallData[z][x] == Goal)
					{
						mapData[z][x] = Goal;
					}

					if (stage1FloorData[z][x] == Floor)
					{
						floorData[z][x] = Floor;
					}
					else if (stage1FloorData[z][x] == Holl)
					{
						floorData[z][x] = Holl;
					}
				}
				//
				else if (isCreateStage_ == 1 && iswhereStage_ == stage2)
				{
					if (stage2Wall[z][x] == none)
					{
						mapData[z][x] = none;
					}
					else if (stage2Wall[z][x] == Block)
					{
						mapData[z][x] = Block;
					}
					else if (stage2Wall[z][x] == BlockObj)
					{
						mapData[z][x] = BlockObj;
					}
					else if (stage2Wall[z][x] == Goal)
					{
						mapData[z][x] = Goal;
					}

					if (stage2Floor[z][x] == Floor)
					{
						floorData[z][x] = Floor;
					}
					else if (stage2Floor[z][x] == Holl)
					{
						floorData[z][x] = Holl;
					}
				}
			}
		}

	}
	isCreateStage_ = 0;
	pauseFlag_ = 1;
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

			//ゴール
			if (mapData[z][x] == Goal)
			{
				modelGoal_->Draw(worldTransform_[z][x], viewProjection_);
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

			//天井
			if (wallData[z][x] == Block)
			{
				modelWall_->Draw(worldTransformWall_[z][x], viewProjection_);
			}

			debugText_->SetPos(20, 140);
			debugText_->Printf(
				"possFlag(%d)", possFlag_);
			debugText_->SetPos(20, 180);
			debugText_->Printf(
				"hollFlag(%d)", hollFlag_);
		}
	}
}

//プレイヤーの手(スプライト描画)
void stageMap::DrawHand()
{
	//ブロック持ってないとき
	if (possFlag_ == 0)
	{
		sprite_hand->Draw();
	}
	//ブロック持ってるとき
	if (possFlag_ == 1)
	{
		sprite_handBox->Draw();
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

				float tx1 = abs(position.x - px);
				float tz1 = abs(position.z - pz);

				float tx2 = abs(position.x - px);
				float tz2 = abs(position.z - pz);


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
				if (dx < 1.3f && dz < 1.3f)
				{
					hollFlag_ = 1;
					if (hollFlag_ == 1)
					{
						return true;
					}
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

bool stageMap::CollisionGoal(float px, float pz)
{
	Vector3 position;

	for (int z = 0; z < mapMax; z++)
	{

		for (int x = 0; x < mapMax; x++)
		{

			if (mapData[z][x] == Goal)
			{

				position.x = worldTransform_[z][x].translation_.x;
				position.z = worldTransform_[z][x].translation_.z;

				float dx = abs(position.x - px);
				float dz = abs(position.z - pz);

				//プレイヤーとの当たり判定
				if (dx < 1.8f && dz < 1.8f)
				{
					isTouchedGoal = 1;
					pauseFlag_ = 0;
					return true;
				}

			}
		}
	}
	return false;
}

void stageMap::ResetStage()
{

	switch (iswhereStage_)
	{
	case tutorial:
		for (int z = 0; z < mapMax; z++)
		{
			for (int x = 0; x < mapMax; x++)
			{
				if (tutoStageData[z][x] == none)
				{
					mapData[z][x] = none;
				}
				else if (tutoStageData[z][x] == Block)
				{
					mapData[z][x] = Block;
				}
				else if (tutoStageData[z][x] == BlockObj)
				{
					mapData[z][x] = BlockObj;
				}
				else if (tutoStageData[z][x] == Goal)
				{
					mapData[z][x] = Goal;

				}

				if (tutoFloorData[z][x] == Floor)
				{
					floorData[z][x] = Floor;
				}
				else if (tutoFloorData[z][x] == Holl)
				{
					floorData[z][x] = Holl;
				}
			}
		}
		break;
	case stage1:
		for (int z = 0; z < mapMax; z++)
		{
			for (int x = 0; x < mapMax; x++)
			{
				if (stage1WallData[z][x] == none)
				{
					mapData[z][x] = none;
				}
				else if (stage1WallData[z][x] == Block)
				{
					mapData[z][x] = Block;
				}
				else if (stage1WallData[z][x] == BlockObj)
				{
					mapData[z][x] = BlockObj;
				}
				else if (stage1WallData[z][x] == Goal)
				{
					mapData[z][x] = Goal;
				}

				if (stage1FloorData[z][x] == Floor)
				{
					floorData[z][x] = Floor;
				}
				else if (stage1FloorData[z][x] == Holl)
				{
					floorData[z][x] = Holl;
				}
			}
		}
		break;
	case stage2:
		for (int z = 0; z < mapMax; z++)
		{
			for (int x = 0; x < mapMax; x++)
			{
				if (stage2Wall[z][x] == none)
				{
					mapData[z][x] = none;
				}
				else if (stage2Wall[z][x] == Block)
				{
					mapData[z][x] = Block;
				}
				else if (stage2Wall[z][x] == BlockObj)
				{
					mapData[z][x] = BlockObj;
				}
				else if (stage2Wall[z][x] == Goal)
				{
					mapData[z][x] = Goal;
				}


				if (stage2Floor[z][x] == Floor)
				{
					floorData[z][x] = Floor;
				}
				else if (stage2Floor[z][x] == Holl)
				{
					floorData[z][x] = Holl;
				}
			}
		}
		break;
	}
	//取ったブロックを所持しているか
	possFlag_ = 0;

	//ゴールに触れたかのフラグ
	isTouchedGoal = 0;

	//ステージを更新するかのフラグ
	isCreateStage_ = 0;

	pauseFlag_ = 1;

	//落とし穴に触れたかのフラグ
	hollFlag_ = 0;

}