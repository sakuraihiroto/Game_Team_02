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

	if (deathFlag_ == 0)
	{
		//������
		if (input_->PushKey(DIK_A)) {playerDir += 0.05f;}

		//�E����
		if (input_->PushKey(DIK_D)) {playerDir -= 0.05f;}

		// ������
		if (input_->PushKey(DIK_S)) {
			float px = worldTransform_.translation_.x + cos(playerDir) / 10;
			float py = worldTransform_.translation_.z + sin(playerDir) / 10;

			if (stageMap_->Collision(px, py) == false)
			{
				move.x += cos(playerDir) / 10;
				move.z += sin(playerDir) / 10;
			}

			if (stageMap_->CollisionHoll(px, py) == true)
			{
				deathFlag_ = true;
			}
		}

		//�����
		if (input_->PushKey(DIK_W)) {
			float px = worldTransform_.translation_.x - cos(playerDir) / 10;
			float py = worldTransform_.translation_.z - sin(playerDir) / 10;

			if (stageMap_->Collision(px, py) == false)
			{
				move.x -= cos(playerDir) / 10;
				move.z -= sin(playerDir) / 10;
			}

			if (stageMap_->CollisionHoll(px, py) == true)
			{
				deathFlag_ = true;
			}
		}
	}
	//��]�\��
	float dir = -playerDir * 180 / 3.14f;
	dir += 90;
	worldTransform_.rotation_.x = dir;
	worldTransform_.rotation_.y = dir;
	worldTransform_.rotation_.z = dir;


	worldTransform_.translation_ += move;

	//�s��̌v�Z
	worldTransform_.matWorld_ = playerMatworld->CreateMatWorld(worldTransform_);
	//�s��̓]��
	worldTransform_.TransferMatrix();

}

//�`�揈��
void Player::Draw(ViewProjection& viewProjection_)
{
	if (deathFlag_ == 0)
	{
		model_->Draw(worldTransform_, viewProjection_);
	}
	// �f�o�b�N�e�L�X�g
	debugText_->SetPos(20, 80);
	debugText_->Printf(
		"worldTranform.x(%d)", worldTransform_.translation_.x);
	debugText_->SetPos(20, 100);
	debugText_->Printf(
		"worldTranform.y(%d)", worldTransform_.translation_.y);
	debugText_->SetPos(20, 120);
	debugText_->Printf(
		"deathFlag(%d)", deathFlag_);

}