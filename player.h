#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "Input.h"
#include "DebugText.h"
#include <assert.h>
#include<memory>
#include<list>
#include "matWorld.h"
#include "ViewProjection.h"
#include "stageMap.h"

class Player
{
public:
	void Initialize(Model* model, stageMap* stageMap);

	///<summary>
	///�X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw(ViewProjection& viewProjection_);

	//���[���h���W���擾
	Vector3 GetWorldPosition();

	//�v���C���[�̍��W
	float GetX() { return worldTransform_.translation_.x; }
	float GetY() { return worldTransform_.translation_.y; }
	float GetZ() { return worldTransform_.translation_.z; }

	float GetPlayerDir() { return playerDir; }

private:

	// ���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;
	//�r���[�v���W�F�N�V����
	ViewProjection viewProjection_;
	// ���f��
	Model* model_ = nullptr;
	// �e�N�X�`���n���h��
	uint32_t textureHandle_ = 0u;
	// �f�o�b�O�e�L�X�g
	DebugText* debugText_ = nullptr;
	// ���͏������邽��
	Input* input_ = nullptr;

	stageMap* stageMap_ = nullptr;

	//���x
	Vector3 velocity_;

	//�p�x
	float playerDir = 0;

	bool deathFlag_ = false;
};
