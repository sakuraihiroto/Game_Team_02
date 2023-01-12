#include "player.h"

// �A�t�B���s��Ăяo��
MatWorld* playerMatworld = nullptr;

void Player::Initialize(Model* model, stageMap* stageMap)
{
	// NULL�|�C���^�`�F�b�N
	assert(model);

	// �����Ƃ��Ď󂯎�����f�[�^�������o�ϐ��ɋL�^����
	model_ = model;
	stageMap_ = stageMap;

	// �V���O���g���C���X�^���X���擾����
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();

	// ���[���h�ϊ��̏�����
	worldTransform_.Initialize();

	//�r���[�v���W�F�N�V�����̏�����
	viewProjection_.Initialize();

}

//���[���h���W������ϐ�
Vector3 Player::GetWorldPosition()
{
	//���[���h���W������ϐ�
	Vector3 worldPos;
	//���[���h�s��̕��s�ړ������擾
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

void Player::Update()
{

	//�L�����N�^�[�̈ړ��x�N�g��
	Vector3 move = { 0, 0, 0 };

	//������
	if (input_->PushKey(DIK_A)) {
		
		float px = worldTransform_.translation_.x - 0.2f;
		float py = worldTransform_.translation_.y;

		if (stageMap_->Collision(px, py) == false)
		{
			move.x -= 0.2f;
		}
	}
	
	//�E����
	if (input_->PushKey(DIK_D)) {
		float px = worldTransform_.translation_.x + 0.2f;
		float py = worldTransform_.translation_.y;

		if (stageMap_->Collision(px, py) == false)
		{
			move.x += 0.2f;
		}
	}

	// ������
	if (input_->PushKey(DIK_S)) {
		float px = worldTransform_.translation_.x;
		float py = worldTransform_.translation_.y - 0.2f;

		if (stageMap_->Collision(px, py) == false)
		{
			move.y -= 0.2f;
		}
	}

	//�����
	if (input_->PushKey(DIK_W)) {
		float px = worldTransform_.translation_.x;
		float py = worldTransform_.translation_.y + 0.2f;

		if (stageMap_->Collision(px, py) == false)
		{
			move.y += 0.2f;
		}
	}


	worldTransform_.translation_ += move;

	//�s��̌v�Z
	worldTransform_.matWorld_ = playerMatworld->CreateMatWorld(worldTransform_);
	//�s��̓]��
	worldTransform_.TransferMatrix();

}

//�`�揈��
void Player::Draw(ViewProjection& viewProjection_)
{
	model_->Draw(worldTransform_, viewProjection_);

	// �f�o�b�N�e�L�X�g
	debugText_->SetPos(20, 80);
	debugText_->Printf(
		"worldTranform.x(%d)",worldTransform_.translation_.x);
	debugText_->SetPos(20, 100);
	debugText_->Printf(
		"worldTranform.y(%d)", worldTransform_.translation_.y);
	
}
