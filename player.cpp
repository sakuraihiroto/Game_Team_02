#include "player.h"

// アフィン行列呼び出し
MatWorld* playerMatworld = nullptr;

void Player::Initialize(Model* model, stageMap* stageMap)
{
	// NULLポインタチェック
	assert(model);

	// 引数として受け取ったデータをメンバ変数に記録する
	model_ = model;
	stageMap_ = stageMap;

	// シングルトンインスタンスを取得する
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();

	// ワールド変換の初期化
	worldTransform_.Initialize();

	//ビュープロジェクションの初期化
	viewProjection_.Initialize();

}

//ワールド座標を入れる変数
Vector3 Player::GetWorldPosition()
{
	//ワールド座標を入れる変数
	Vector3 worldPos;
	//ワールド行列の平行移動分を取得
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

void Player::Update()
{
	float px = worldTransform_.translation_.x;
	float pz = worldTransform_.translation_.z;
	//キャラクターの移動ベクトル
	Vector3 move = { 0, 0, 0 };

	if (deathFlag_ == 0 && stageMap_->CollisionGoal(px, pz) == false)
	{
		

		//左方向
		if (input_->PushKey(DIK_A)) {

			px = worldTransform_.translation_.x - 0.2f;
			pz = worldTransform_.translation_.z;

			if (stageMap_->Collision(px, pz) == false)
			{
				move.x -= 0.2f;
			}

			if (stageMap_->CollisionHoll(px, pz) == true)
			{
				deathFlag_ = 1;
			}
		}

		//右方向
		if (input_->PushKey(DIK_D)) {
			px = worldTransform_.translation_.x + 0.2f;
			pz = worldTransform_.translation_.z;

			if (stageMap_->Collision(px, pz) == false)
			{
				move.x += 0.2f;
			}

			if (stageMap_->CollisionHoll(px, pz) == true)
			{
				deathFlag_ = 1;
			}
		}

		// 下方向
		if (input_->PushKey(DIK_S)) {
			px = worldTransform_.translation_.x;
			pz = worldTransform_.translation_.z - 0.2f;

			if (stageMap_->Collision(px, pz) == false)
			{
				move.z -= 0.2f;
			}

			if (stageMap_->CollisionHoll(px, pz) == true)
			{
				deathFlag_ = 1;
			}
		}

		//上方向
		if (input_->PushKey(DIK_W)) {
			px = worldTransform_.translation_.x;
			pz = worldTransform_.translation_.z + 0.2f;

			if (stageMap_->Collision(px, pz) == false)
			{
				move.z += 0.2f;
			}

			if (stageMap_->CollisionHoll(px, pz) == true)
			{
				deathFlag_ = 1;
			}
		}


		if (input_->TriggerKey(DIK_SPACE))
		{
			px = worldTransform_.translation_.x;
			pz = worldTransform_.translation_.z;

			stageMap_->PutBlock(px, pz);
			stageMap_->DeleteBlock(px, pz);


				
		}

		
		
		
	}

	if (input_->TriggerKey(DIK_R))
	{
		deathFlag_ = 0;
		worldTransform_.translation_ = { 0,0,0 };
		stageMap_->ResetStage();
	}

	if (stageMap_->CollisionGoal(px, pz) == true)
	{
		if (input_->TriggerKey(DIK_SPACE))
		{
			switch (stageMap_->iswhereStage_)
			{
			case 1:
				worldTransform_.translation_ = { 0,0,0 };
				break;

			case 2:
				worldTransform_.translation_ = { 0,0,0 };
				break;
			}

			stageMap_->SetPauseFlag_();

		}
	}
	worldTransform_.translation_ += move;

	//行列の計算
	worldTransform_.matWorld_ = playerMatworld->CreateMatWorld(worldTransform_);
	//行列の転送
	worldTransform_.TransferMatrix();

}

//描画処理
void Player::Draw(ViewProjection& viewProjection_)
{
	if (deathFlag_ == 0)
	{
		model_->Draw(worldTransform_, viewProjection_);
	}

	// デバックテキスト
	debugText_->SetPos(20, 80);
	debugText_->Printf(
		"worldTransform.x(%lf)",worldTransform_.translation_.x);
	debugText_->SetPos(20, 100);
	debugText_->Printf(
		"worldTransform.z(%lf)", worldTransform_.translation_.z);

	
}
