#pragma once

#include "Model.h"
#include "WorldTransform.h"
#include "TextureManager.h"
#include "matWorld.h"
#include "Input.h"
#include "player.h"

class Stage
{

public:

	void Initialize(Model* model);

	void Update();

	void Draw(ViewProjection viewProjection);

private:

	//���[���h�ϊ��f�[�^
	WorldTransform worldTransform_[2];
	//�f�o�b�N�e�L�X�g
	DebugText* debugText_ = nullptr;
	//�r���[�v���W�F�N�V����
	ViewProjection viewProjection_;
	// ���͏������邽��
	Input* input_ = nullptr;
	//���f��
	Model* model_ = nullptr;
	Model* modelPlayer_ = nullptr;
	//�v���C���[
	Player* player_ = nullptr;

	//�X�e�[�W�ړ��͈�
	const float stageMoveLimitX = 10.0f;
	const float stageMoveLimitZ = 20.0f;

	

};

