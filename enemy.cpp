#pragma once
#include<assert.h>
#include"enemy.h"
// �A�t�B���s��Ăяo��
MatWorld* enemyMatworld = nullptr;

void Enemy::Initialize(Model* model, const Vector3& position) {

	//NULL�|�C���^�`�F�b�N
	assert(model);

	model_ = model;

	//�e�N�X�`���ǂݍ���
	textureHandle_ = TextureManager::Load("yellow.png");

	//input_ = Input::GetInstance();
	//���[���h�ϊ��̏�����
	worldTransform_.Initialize();

	//�������W���Z�b�g
	worldTransform_.translation_ = position;

	//�e��ݒ�
	//worldTransform_.parent_ =stage->GetWorldTransformPtr();
}

void Enemy::Update()
{
	//�s��̌v�Z
	//stage->GetMatWorld() = enemyMatworld->CreateMatWorld(stage->GetWorldTransform());
	//�s��̓]��
	//worldTransform_.TransferMatrix();

	//�s��̌v�Z
	worldTransform_.matWorld_ = enemyMatworld->CreateMatWorld(worldTransform_);

	/*if (worldTransform_.parent_ != nullptr)
	{
		worldTransform_.matWorld_ *= stage->GetMatWorld();
	}*/
	//�s��̓]��
	worldTransform_.TransferMatrix();
}

Vector3 Enemy::GetWorldPosition()
{
	// ���[���h���W������ϐ�
	Vector3 worldPos;
	// ���[���h�s��̕��s�ړ��������擾(���[���h���W)
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

WorldTransform* Enemy::GetWorldTransform()
{
	return &worldTransform_;
}

//�Փ˔���
void Enemy::OnCollision()
{
	isDead_ = true;
}
void Enemy::Draw(ViewProjection& viewProjection)
{
	//���f���̕`��
	model_->Draw(worldTransform_, viewProjection,textureHandle_);
}
