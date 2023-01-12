#include "player.h"

// �A�t�B���s��Ăяo��
MatWorld* playerMatworld = nullptr;

void Player::Initialize(Model* model)
{
	// NULL�|�C���^�`�F�b�N
	assert(model);

	// �����Ƃ��Ď󂯎�����f�[�^�������o�ϐ��ɋL�^����
	model_ = model;

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
		leftMoveFlag = 1;
		rightMoveFlag = 0;
		upMoveFlag = 0;
		downMoveFlag = 0;
	}
	if (leftMoveFlag == 1)
	{
		move.x -= 0.2f;
	}
	//�E����
	if (input_->PushKey(DIK_D)) {
		rightMoveFlag = 1;
		leftMoveFlag = 0;
		downMoveFlag = 0;
		upMoveFlag = 0;
	}
	if (rightMoveFlag == 1)
	{
		move.x += 0.2f;
	}
	// ������
	if (input_->PushKey(DIK_S)) {
		downMoveFlag = 1;
		upMoveFlag = 0;
		rightMoveFlag = 0;
		leftMoveFlag = 0;
	}
	if (downMoveFlag == 1)
	{
		move.y -= 0.2f;
	}
	//�����
	if (input_->PushKey(DIK_W)) {
		upMoveFlag = 1;
		downMoveFlag = 0;
		leftMoveFlag = 0;
		rightMoveFlag = 0;
	}
	if (upMoveFlag == 1)
	{
		move.y += 0.2f;
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
		"leftMoveFlag(%d)",leftMoveFlag);
	// �f�o�b�N�e�L�X�g
	debugText_->SetPos(20, 100);
	debugText_->Printf(
		"rightMoveFlag(%d)", rightMoveFlag);
	// �f�o�b�N�e�L�X�g
	debugText_->SetPos(20, 120);
	debugText_->Printf(
		"upMoveFlag(%d)", upMoveFlag);
	// �f�o�b�N�e�L�X�g
	debugText_->SetPos(20, 140);
	debugText_->Printf(
		"downMoveFlag(%d)", downMoveFlag);
}
