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

		//�E����
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

		// ������
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

		//�����
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
		"worldTransform.x(%lf)",worldTransform_.translation_.x);
	debugText_->SetPos(20, 100);
	debugText_->Printf(
		"worldTransform.z(%lf)", worldTransform_.translation_.z);

	
}
