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


	worldTransform_.translation_ = {};
	// ���[���h�ϊ��̏�����	{0,0,0}

	worldTransform_.translation_ = { -7 + x * 2.0f, 0, 10 + y * -2.0f };
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
	float px = worldTransform_.translation_.x;
	float py = worldTransform_.translation_.y;
	float pz = worldTransform_.translation_.z;

	mousePrePos_ = mousePos_;

	GetCursorPos(&mousePos_);

	float mouseMoveX = mousePos_.x - mousePrePos_.x;
	float mouseMoveY = mousePos_.y - mousePrePos_.y;


	if (deathFlag_ == 0 && stageMap_->CollisionGoal(px, pz) == false)
	{
		//������
		if (input_->PushKey(DIK_A)) { playerDir += 0.05f; }

		//�E����
		if (input_->PushKey(DIK_D)) { playerDir -= 0.05f; }

		// ������
		if (input_->PushKey(DIK_S)) {
			px = worldTransform_.translation_.x + cos(playerDir) / 10;
			py = worldTransform_.translation_.z + sin(playerDir) / 10;
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
			px = worldTransform_.translation_.x - cos(playerDir) / 10;
			py = worldTransform_.translation_.z - sin(playerDir) / 10;

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

		//�E����(�}�E�X���_)
		if (mouseMoveX < 0) { playerDir += 0.03f; }

		//������(�}�E�X���_)
		if (mouseMoveX > 0) { playerDir -= 0.03f; }

		//�����(�}�E�X���_)
		if (mouseMoveY > 0) { playerDirY += 0.03f; }

		//������(�}�E�X���_)
		if (mouseMoveY < 0) { playerDirY -= 0.03f; }

		//���_���
		if (playerDirY > 1.2f)
		{
			playerDirY -= 0.03f;
		}

		if (playerDirY < -1.2f)
		{
			playerDirY += 0.03f;
		}


		if (input_->TriggerKey(DIK_Q))
		{
			px = worldTransform_.translation_.x;
			pz = worldTransform_.translation_.z;

			stageMap_->PutBlock(px, pz);
			stageMap_->DeleteBlock(px, pz);


		}
		//��]�\��
		float dir = -playerDir * 180 / 3.14f;
		dir += 90;
		worldTransform_.rotation_.x = dir;
		worldTransform_.rotation_.y = dir;
		worldTransform_.rotation_.z = dir;

		if (stageMap_->CollisionGoal(px, pz) == true)
		{
			//��~


			if (input_->TriggerKey(DIK_SPACE))
			{
				switch (stageMap_->iswhereStage_)
				{
				case tutorial:
					worldTransform_.translation_ = { -7 + x * 2.0f, 0, 10 + y * -2.0f };

					break;

				case stage1:
					worldTransform_.translation_ = { -7 + x1 * 2.0f, 0, 10 + y1 * -2.0f };

					break;

				case stage2:
					worldTransform_.translation_ = { -14 + x2 * 2.0f, 0, 10 + y2 * -2.0f };

					break;
				}
			}
		}


		worldTransform_.translation_ += move;

		//�s��̌v�Z
		worldTransform_.matWorld_ = playerMatworld->CreateMatWorld(worldTransform_);
		//�s��̓]��
		worldTransform_.TransferMatrix();

	}

	if (stageMap_->CollisionGoal(px, pz) == true)
	{
		if (input_->TriggerKey(DIK_SPACE))
		{
			switch (stageMap_->iswhereStage_)
			{
			case 1:
				worldTransform_.translation_ = { 0,0,0 };
				break;

			case 2:
				worldTransform_.translation_ = { 0,0,0 };
				break;
			}

			stageMap_->SetPauseFlag_();

		}
	}

	worldTransform_.translation_ += move;

	//�s��̌v�Z
	worldTransform_.matWorld_ = playerMatworld->CreateMatWorld(worldTransform_);
	//�s��̓]��
	worldTransform_.TransferMatrix();

}

//�������֐�
void Player::ResetPlayer()
{
	deathFlag_ = 0;
	playerDir = 4;
	worldTransform_.translation_ = { -7 + x * 2.0f, 0, 10 + y * -2.0f };
	x = 2;
	y = 7;
	x1 = 1;
	y1 = 6;
	x2 = 1;
	y2 = 10;
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
		"worldTransform.x(%lf)", worldTransform_.translation_.x);
	debugText_->SetPos(20, 100);
	debugText_->Printf(
		"worldTransform.z(%lf)", worldTransform_.translation_.z);


}