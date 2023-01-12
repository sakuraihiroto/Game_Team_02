#pragma once
#include<assert.h>
#include"enemy.h"
// アフィン行列呼び出し
MatWorld* enemyMatworld = nullptr;

void Enemy::Initialize(Model* model, const Vector3& position) {

	//NULLポインタチェック
	assert(model);

	model_ = model;

	//テクスチャ読み込み
	textureHandle_ = TextureManager::Load("yellow.png");

	//input_ = Input::GetInstance();
	//ワールド変換の初期化
	worldTransform_.Initialize();

	//初期座標をセット
	worldTransform_.translation_ = position;

	//親を設定
	//worldTransform_.parent_ =stage->GetWorldTransformPtr();
}

void Enemy::Update()
{
	//行列の計算
	//stage->GetMatWorld() = enemyMatworld->CreateMatWorld(stage->GetWorldTransform());
	//行列の転送
	//worldTransform_.TransferMatrix();

	//行列の計算
	worldTransform_.matWorld_ = enemyMatworld->CreateMatWorld(worldTransform_);

	/*if (worldTransform_.parent_ != nullptr)
	{
		worldTransform_.matWorld_ *= stage->GetMatWorld();
	}*/
	//行列の転送
	worldTransform_.TransferMatrix();
}

Vector3 Enemy::GetWorldPosition()
{
	// ワールド座標を入れる変数
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得(ワールド座標)
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

WorldTransform* Enemy::GetWorldTransform()
{
	return &worldTransform_;
}

//衝突判定
void Enemy::OnCollision()
{
	isDead_ = true;
}
void Enemy::Draw(ViewProjection& viewProjection)
{
	//モデルの描画
	model_->Draw(worldTransform_, viewProjection,textureHandle_);
}
