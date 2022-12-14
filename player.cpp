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

	//�L�����N�^�[�̈ړ��x�N�g��
	Vector3 move = { 0,2,0 };//���W{x,y,z}

	//�������W���Z�b�g
	worldTransform_.translation_ = move;

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

}

//�`�揈��
void Player::Draw(ViewProjection& viewProjection_,WorldTransform worldTransform)
{
	
	//// �f�o�b�N�e�L�X�g
	//debugText_->SetPos(20, 80);
	//debugText_->Printf(
	//	"leftMoveFlag(%d)",leftMoveFlag);
	//// �f�o�b�N�e�L�X�g
	//debugText_->SetPos(20, 100);
	//debugText_->Printf(
	//	"rightMoveFlag(%d)", rightMoveFlag);
	//// �f�o�b�N�e�L�X�g
	//debugText_->SetPos(20, 120);
	//debugText_->Printf(
	//	"upMoveFlag(%d)", upMoveFlag);
	//// �f�o�b�N�e�L�X�g
	//debugText_->SetPos(20, 140);
	//debugText_->Printf(
	//	"downMoveFlag(%d)", downMoveFlag);
}
