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
#include "WinApp.h"


class Player
{
public:
	void Initialize(Model* model, stageMap* stageMap);

	void Update();

	void ResetPlayer();

	void Draw(ViewProjection& viewProjection_);

	//���[���h���W���擾
	Vector3 GetWorldPosition();

	//�v���C���[�̍��W
	float GetX() { return worldTransform_.translation_.x; }
	float GetY() { return worldTransform_.translation_.y; }
	float GetZ() { return worldTransform_.translation_.z; }

	float GetPlayerDir() { return playerDir; }

	float GetPlayerDirY() { return playerDirY; }

	int GetScene(uint32_t& scene) { return scene_ = scene; }
private:

	enum �V�[��
	{
		title,				//0
		tutorial,			//1
		stage1,				//2
		stage2,				//3
		gameOver,			//4
		gameClear			//5
	};

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

	//�v���C���[�̌���
	float playerDir = 4;

	float playerDirY = 0;
	int deathFlag_ = 0;

	POINT mousePos_ = { 0,0 };
	POINT mousePrePos_ = { 0,0 };

	//�v���C���[�����ʒu
	uint32_t x = 2;
	uint32_t y = 7;
	uint32_t x1 = 1;
	uint32_t y1 = 6;
	uint32_t x2 = 1;
	uint32_t y2 = 10;

	uint32_t scene_ = 0;


};