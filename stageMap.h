#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "MatWorld.h"
#include "ViewProjection.h"
#include <DirectXMath.h>
#include "DebugText.h"
#include "Input.h"
#include "Sprite.h"
#include "TextureManager.h"


using namespace DirectX;


class stageMap
{

public:
	void Initialize();

	void Update();

	void Draw(ViewProjection viewProjection_);

	void DrawHand();

	bool Collision(float px, float pz);

	//���Ƃ����̔��肷��֐�
	bool CollisionHoll(float px, float pz);

	//�S�[���𔻒肷��֐�
	bool CollisionGoal(float px, float pz);

	//�u���b�N����锻�������֐�
	void DeleteBlock(float px, float pz);

	//�u���b�N��u�����������֐�
	void PutBlock(float px, float pz);

	void ResetStage();

	void SetPauseFlag_()
	{
		pauseFlag_ = 0;
	}

	int GethollFlag() { return hollFlag_; }

	//�u���b�N�������
	int countPossBlock_ = 2;

	int GetScene(uint32_t& scene) { return scene_ = scene; }
	int SetScene() { return scene_; }

	bool SetGoal(bool& goalFlag) { return goalFlag = isTouchedGoal; }

	bool SetPauseFlag(bool& pauseFlag) { return pauseFlag = pauseFlag_; }

public:
	static const int mapMax = 12;

	static int iswhereStage_;
private:

	//�ǂ̃u���b�N�Ή��\

	WorldTransform worldTransform_[mapMax][mapMax] = {};
	WorldTransform worldTransformCeiling_[mapMax][mapMax] = {};
	WorldTransform worldTransformFloor_[mapMax][mapMax] = {};
	WorldTransform worldTransformWall_[mapMax][mapMax] = {};

	enum Wall_Block
	{
		none,		//�Ȃ�
		Block,		//�u���b�N
		BlockObj,	//�ړ��s�u���b�N
		Goal		//�S�[��
	};

	enum Floor_Block
	{
		Floor,			//�u���b�N
		Holl,			//���Ƃ���
		FilledFloor		//���߂��t���A(�����ɂ͊֌W�Ȃ�)
	};

	enum Stage
	{
		Stage1 = 1,
		Stage2,
		Stage3
	};

	enum Scene
	{
		title,				//0
		tutorial,			//1
		stage1,				//2
		stage2,				//3
		gameOver,			//4
		gameClear			//5
	};

	//�}�b�v�f�[�^
	int mapData[mapMax][mapMax] = {//[11][2]
		{2,2,2,2,2},
		{2,2,3,2,2},
		{2,2,0,2,2},
		{2,2,0,2,2},
		{2,2,0,2,2},
		{2,2,1,2,2},
		{2,2,0,2,2},
		{2,2,0,2,2},
		{2,2,2,2,2}
	};

	//�`���[�g���A���}�b�v
	int tutoStageData[mapMax][mapMax] = {//[7][2]
		{2,2,2,2,2},
		{2,2,3,2,2},
		{2,2,0,2,2},
		{2,2,0,2,2},
		{2,2,0,2,2},
		{2,2,1,2,2},
		{2,2,0,2,2},
		{2,2,0,2,2},
		{2,2,2,2,2}
	};

	int tutoFloorData[mapMax][mapMax] = {
		{0,0,0,0,0},
		{0,0,0,0,0},
		{0,0,0,0,0},
		{0,0,1,0,0},
		{0,0,0,0,0},
		{0,0,0,0,0},
		{0,0,0,0,0},
		{0,0,0,0,0},
		{0,0,0,0,0}
	};

	
	//�X�e�[�W1
	int stage1WallData[mapMax][mapMax] = {//[6][1]
		{2,2,2,2,2,2,2,2},
		{2,1,1,0,0,0,0,2},
		{2,1,1,0,1,0,3,2},
		{2,1,1,0,0,0,1,2},
		{2,0,0,0,1,0,1,2},
		{2,1,1,0,1,0,1,2},
		{2,0,0,0,0,0,1,2},
		{2,0,0,1,1,1,1,2},
		{2,2,2,2,2,2,2,2}
	};

	int stage1FloorData[mapMax][mapMax] =
	{
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,1,0},
		{0,0,0,0,0,1,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,1,0,0},
		{0,0,0,1,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0}
	};


	//�X�e�[�W2
	int stage2Wall[mapMax][mapMax] = {
	{ 2, 2, 2, 2, 2, 2, 2, 2, 2 },
	{ 2, 0, 0, 0, 1, 0, 1, 0, 2 },
	{ 2, 0, 1, 0, 1, 0, 1, 0, 2 },
	{ 2, 0, 1, 0, 1, 0, 0, 0, 2 },
	{ 2, 0, 0, 0, 1, 0, 1, 0, 2 },
	{ 2, 0, 1, 0, 0, 0, 1, 0, 2 },
	{ 2, 0, 1, 0, 1, 0, 1, 3, 2 },
	{ 2, 0, 1, 0, 1, 1, 1, 1, 2 },
	{ 2, 0, 1, 0, 1, 0, 0, 0, 2 },
	{ 2, 0, 0, 0, 1, 1, 1, 0, 2 },
	{ 2, 0, 0, 0, 1, 0, 0, 0, 2 },
	{ 2, 2, 2, 2, 2, 2, 2, 2, 2 }
	};

	int stageSakurai[mapMax][mapMax] = {
	{2, 2, 2, 2, 2, 2, 2, 2, 2},
	{2, 0, 3, 0, 1, 3, 1, 0, 2},
	{2, 0, 1, 0, 1, 0, 1, 0, 2},
	{2, 0, 1, 0, 1, 0, 0, 0, 2},
	{2, 0, 3, 0, 1, 0, 1, 0, 2},
	{2, 0, 1, 0, 3, 0, 1, 3, 2},
	{2, 0, 1, 0, 1, 0, 1, 4, 2},
	{2, 0, 1, 0, 1, 1, 1, 1, 2},
	{2, 3, 1, 3, 1, 0, 0, 0, 2},
	{2, 0, 0, 0, 1, 1, 1, 3, 2},
	{2, 0, 0, 0, 1, 0, 0, 0, 2},
	{2, 2, 2, 2, 2, 2, 2, 2, 2}
	};

	int floorSakurai[mapMax][mapMax] = {
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 1, 0, 0, 1, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 1, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 1, 0, 0, 1, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 1, 0, 1, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 1, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0}
	};

	int stage2Floor[mapMax][mapMax] = {
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 1, 0, 0, 1, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 1, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 1, 0, 0, 1, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 1, 0, 1, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 1, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0 }
	};

	int floorData[mapMax][mapMax] = {
		{0,0,0,0,0},
		{0,0,0,0,0},
		{0,0,0,0,0},
		{0,0,1,0,0},
		{0,0,0,0,0},
		{0,0,0,0,0},
		{0,0,0,0,0},
		{0,0,0,0,0},
		{0,0,0,0,0}

	};

	int touchData[mapMax][mapMax] = {
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0 }
	};


	//�V��
	int wallData[mapMax][mapMax] = {
		{1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1}
	};

	int CeilingData[mapMax][mapMax] = {
		{1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1}
	};

	//���f��
	Model* modelWall_ = nullptr;
	Model* modelChain_ = nullptr;
	Model* modelHoll_ = nullptr;
	Model* modelFloor_ = nullptr;
	Model* modelGoal_ = nullptr;

	//�e�N�X�`���n���h��
	uint32_t textureHandle_hand_ = 0;
	uint32_t textureHandle_handBox_ = 0;

	//�X�v���C�g
	Sprite* sprite_hand = nullptr;
	Sprite* sprite_handBox = nullptr;

	MatWorld* matWorld_ = nullptr;

	// �f�o�b�O�e�L�X�g
	DebugText* debugText_ = nullptr;

	// ���͏������邽��
	Input* input_ = nullptr;

	//�V�[��
	uint32_t scene_ = 0;

	//������u���b�N���������Ă��邩
	int possFlag_ = 0;

	//�S�[���ɐG�ꂽ���̃t���O
	int isTouchedGoal = 0;

	//�X�e�[�W���X�V���邩�̃t���O
	int isCreateStage_ = 0;

	int pauseFlag_ = 1;

	//���Ƃ����ɐG�ꂽ���̃t���O
	int hollFlag_ = 0;

};