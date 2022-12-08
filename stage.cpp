#include "stage.h"
#include <cassert>

MatWorld* stageMatworld = nullptr;

void Stage::Initialize(Model* model)
{
	assert(model);

	model_ = model;
	worldTransform_.Initialize();

	input_ = Input::GetInstance();
	//s—ñ‚ÌŒvŽZ
	worldTransform_.matWorld_ = stageMatworld->CreateMatWorld(worldTransform_);
	//s—ñ‚Ì“]‘—
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
	

	//s—ñ‚ÌŒvŽZ
	worldTransform_.matWorld_ = stageMatworld->CreateMatWorld(worldTransform_);
	//s—ñ‚Ì“]‘—
	worldTransform_.TransferMatrix();

}

void Stage::Draw(ViewProjection viewProjection_)
{
	model_->Draw(worldTransform_, viewProjection_);
}

