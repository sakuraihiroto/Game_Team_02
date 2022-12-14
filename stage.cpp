#include "stage.h"
#include <cassert>

MatWorld* stageMatworld = nullptr;

void Stage::Initialize(Model* model)
{
	assert(model);

	model_ = model;

	input_ = Input::GetInstance();

	//親(ステージ)
	worldTransform_[0].Initialize();
	//子(プレイヤー)
	worldTransform_[1].Initialize();
	worldTransform_[1].translation_ = { 0,4.5f,0 };
	worldTransform_[1].parent_ = player_->GatWorldPlayer();
	
	//行列の計算
	worldTransform_[0].matWorld_ = stageMatworld->CreateMatWorld(worldTransform_[0]);
	//行列の転送
	worldTransform_[0].TransferMatrix();
	
}

void Stage::Update()
{
	if (input_->PushKey(DIK_D))
	{
		worldTransform_[0].rotation_.z += 0.01f;
		worldTransform_[1].rotation_.z += 0.01f;
	}
	if (input_->PushKey(DIK_A))
	{
		worldTransform_[0].rotation_.z -= 0.01f;
		worldTransform_[1].rotation_.z -= 0.01f;
	}
	if (input_->PushKey(DIK_S))
	{
		worldTransform_[0].rotation_.x += 0.01f;
		worldTransform_[1].rotation_.x += 0.01f;
	}
	if (input_->PushKey(DIK_W))
	{
		worldTransform_[0].rotation_.x -= 0.01f;
		worldTransform_[1].rotation_.x -= 0.01f;
	}

	//行列の計算
	worldTransform_[0].matWorld_ = stageMatworld->CreateMatWorld(worldTransform_[0]);
	//行列の転送
	worldTransform_[0].TransferMatrix();

	//子の更新
	worldTransform_[1].matWorld_ = stageMatworld->CreateMatWorld(worldTransform_[1]);

	if (worldTransform_[1].parent_ != nullptr)
	{
		worldTransform_[1].matWorld_ *= worldTransform_[1].parent_->matWorld_;
	}
	
	worldTransform_[1].TransferMatrix();
}

void Stage::Draw(ViewProjection viewProjection_)
{

	model_->Draw(worldTransform_[0], viewProjection_);
	player_->Draw(viewProjection_, worldTransform_[1]);
	
}

