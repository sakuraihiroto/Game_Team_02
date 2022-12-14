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

	//ワールド変換の初期化
	worldTransform_.Initialize();

	//初期座標をセット
	worldTransform_.translation_ = position;

}

void Enemy::Update()
{
	//行列の計算
	worldTransform_.matWorld_ = enemyMatworld->CreateMatWorld(worldTransform_);
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
