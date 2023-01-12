#include "stage.h"
#include <cassert>

MatWorld* stageMatworld = nullptr;

void Stage::Initialize(Model* model)
{
	assert(model);

	model_ = model;
	//親(0番)
	worldTransform_.Initialize();
	//キーボード入力
	input_ = Input::GetInstance();
	//行列の計算
	worldTransform_.matWorld_ = stageMatworld->CreateMatWorld(worldTransform_);
	//行列の転送
	worldTransform_.TransferMatrix();

	
}

void Stage::Update()
{
	if (input_->PushKey(DIK_1))
	{
		worldTransform_.rotation_.z += 0.01f;
	}
	if (input_->PushKey(DIK_2))
	{
		worldTransform_.rotation_.z -= 0.01f;
	}
	if (input_->PushKey(DIK_3))
	{
		worldTransform_.rotation_.x += 0.01f;
	}
	if (input_->PushKey(DIK_4))
	{
		worldTransform_.rotation_.x -= 0.01f;
	}

	//行列の計算
	worldTransform_.matWorld_ = stageMatworld->CreateMatWorld(worldTransform_);
	//行列の転送
	worldTransform_.TransferMatrix();
}

WorldTransform* Stage::GetWorldTransformPtr()
{
	return &worldTransform_;
}

WorldTransform Stage::GetWorldTransform()
{
	return worldTransform_;
}

Matrix4 Stage::GetMatWorld()
{
	Matrix4 worldMatWorld;
	worldMatWorld.m[0][0] = worldTransform_.matWorld_.m[0][0];
	worldMatWorld.m[0][1] = worldTransform_.matWorld_.m[0][1];
	worldMatWorld.m[0][2] = worldTransform_.matWorld_.m[0][2];
	worldMatWorld.m[0][3] = worldTransform_.matWorld_.m[0][3];
	worldMatWorld.m[1][0] = worldTransform_.matWorld_.m[1][0];
	worldMatWorld.m[1][1] = worldTransform_.matWorld_.m[1][1];
	worldMatWorld.m[1][2] = worldTransform_.matWorld_.m[1][2];
	worldMatWorld.m[1][3] = worldTransform_.matWorld_.m[1][3];
	worldMatWorld.m[2][0] = worldTransform_.matWorld_.m[2][0];
	worldMatWorld.m[2][1] = worldTransform_.matWorld_.m[2][1];
	worldMatWorld.m[2][2] = worldTransform_.matWorld_.m[2][2];
	worldMatWorld.m[2][3] = worldTransform_.matWorld_.m[2][3];
	worldMatWorld.m[3][0] = worldTransform_.matWorld_.m[3][0];
	worldMatWorld.m[3][1] = worldTransform_.matWorld_.m[3][1];
	worldMatWorld.m[3][2] = worldTransform_.matWorld_.m[3][2];
	worldMatWorld.m[3][3] = worldTransform_.matWorld_.m[3][3];
	return worldMatWorld;
}

void Stage::Draw(ViewProjection viewProjection_)
{
	model_->Draw(worldTransform_, viewProjection_);
}

