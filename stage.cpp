#include "stage.h"
#include <cassert>

MatWorld* stageMatworld = nullptr;

void Stage::Initialize(Model* model)
{
	assert(model);

	model_ = model;

	input_ = Input::GetInstance();

	//�e(�X�e�[�W)
	worldTransform_[0].Initialize();
	//�q(�v���C���[)
	worldTransform_[1].Initialize();
	worldTransform_[1].translation_ = { 0,4.5f,0 };
	worldTransform_[1].parent_ = player_->GatWorldPlayer();
	
	//�s��̌v�Z
	worldTransform_[0].matWorld_ = stageMatworld->CreateMatWorld(worldTransform_[0]);
	//�s��̓]��
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

	//�s��̌v�Z
	worldTransform_[0].matWorld_ = stageMatworld->CreateMatWorld(worldTransform_[0]);
	//�s��̓]��
	worldTransform_[0].TransferMatrix();

	//�q�̍X�V
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

