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

	//キャラクターの移動ベクトル
	Vector3 move = { 0, 0, 0 };

	if (deathFlag_ == 0)
	{
		//左方向
		if (input_->PushKey(DIK_A)) {

			float px = worldTransform_.translation_.x - 0.2f;
			float pz = worldTransform_.translation_.z;

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
			float px = worldTransform_.translation_.x + 0.2f;
			float pz = worldTransform_.translation_.z;

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
			float px = worldTransform_.translation_.x;
			float pz = worldTransform_.translation_.z - 0.2f;

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
			float px = worldTransform_.translation_.x;
			float pz = worldTransform_.translation_.z + 0.2f;

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
			float px = worldTransform_.translation_.x;
			float pz = worldTransform_.translation_.z;

			stageMap_->PutBlock(px, pz);
			stageMap_->DeleteBlock(px, pz);


				
		}

		if (input_->TriggerKey(DIK_R))
		{
			stageMap_->ResetStage();
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
