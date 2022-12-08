#pragma once

#include "Model.h"
#include "WorldTransform.h"
#include "TextureManager.h"
#include "Input.h"
#include "matWorld.h"

class Stage
{

public:

	void Initialize(Model* model);

	void Update();

	void Draw(ViewProjection viewProjection);

private:

	//���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;
	//�r���[�v���W�F�N�V����
	ViewProjection viewProjection_;
	// ���͏������邽��
	Input* input_ = nullptr;
	//���f��
	Model* model_ = nullptr;


};

