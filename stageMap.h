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

	//落とし穴の判定する関数
	bool CollisionHoll(float px, float pz);

	//ゴールを判定する関数
	bool CollisionGoal(float px, float pz);

	//ブロックを取る判定をする関数
	void DeleteBlock(float px, float pz);

	//ブロックを置く判定をする関数
	void PutBlock(float px, float pz);

	void ResetStage();

	void SetPauseFlag_()
	{
		pauseFlag_ = 0;
	}

	int GethollFlag() { return hollFlag_; }

	//ブロックを取れる回数
	int countPossBlock_ = 2;

	int GetScene(uint32_t& scene) { return scene_ = scene; }
	int SetScene() { return scene_; }

	bool SetGoal(bool& goalFlag) { return goalFlag = isTouchedGoal; }

	bool SetPauseFlag(bool& pauseFlag) { return pauseFlag = pauseFlag_; }

public:
	static const int mapMax = 12;

	static int iswhereStage_;
private:

	//壁のブロック対応表

	WorldTransform worldTransform_[mapMax][mapMax] = {};
	WorldTransform worldTransformCeiling_[mapMax][mapMax] = {};
	WorldTransform worldTransformFloor_[mapMax][mapMax] = {};
	WorldTransform worldTransformWall_[mapMax][mapMax] = {};

	enum Wall_Block
	{
		none,		//なし
		Block,		//ブロック
		BlockObj,	//移動不可ブロック
		Goal		//ゴール
	};

	enum Floor_Block
	{
		Floor,			//ブロック
		Holl,			//落とし穴
		FilledFloor		//埋めたフロア(生成には関係なし)
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

	//マップデータ
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

	//チュートリアルマップ
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

	
	//ステージ1
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


	//ステージ2
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


	//天井
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

	//モデル
	Model* modelWall_ = nullptr;
	Model* modelChain_ = nullptr;
	Model* modelHoll_ = nullptr;
	Model* modelFloor_ = nullptr;
	Model* modelGoal_ = nullptr;

	//テクスチャハンドル
	uint32_t textureHandle_hand_ = 0;
	uint32_t textureHandle_handBox_ = 0;

	//スプライト
	Sprite* sprite_hand = nullptr;
	Sprite* sprite_handBox = nullptr;

	MatWorld* matWorld_ = nullptr;

	// デバッグテキスト
	DebugText* debugText_ = nullptr;

	// 入力処理するため
	Input* input_ = nullptr;

	//シーン
	uint32_t scene_ = 0;

	//取ったブロックを所持しているか
	int possFlag_ = 0;

	//ゴールに触れたかのフラグ
	int isTouchedGoal = 0;

	//ステージを更新するかのフラグ
	int isCreateStage_ = 0;

	int pauseFlag_ = 1;

	//落とし穴に触れたかのフラグ
	int hollFlag_ = 0;

};