#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "MatWorld.h"
#include "ViewProjection.h"
#include <DirectXMath.h>
#include "DebugText.h"
#include "Input.h"


using namespace DirectX;


class stageMap
{

public:
	void Initialize();

	void Draw(ViewProjection viewProjection_);

	void DrawHand();

	bool Collision(float px, float pz);

	bool CollisionHoll(float px, float pz);

	void DeleteBlock(float px, float pz);

	void PutBlock(float px, float pz);

	void ResetStage();
	
	int GetScene(uint32_t& scene) { return scene_ = scene; }

	void ChangeMap();

public:
	static const int mapMax = 12;


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
		Floor,			//床
		Holl,			//落とし穴
		FilledFloor		//埋めたフロア(生成には関係なし)
	};

	enum シーン
	{
		title,				//0
		tutorial,			//1
		stage1,				//2
		stage2,				//3
		gameOver,			//4
		gameClear			//5
	};

	/*int mapData[mapMax][mapMax] = {
		{2,1,1,1,1,1,1,1,1,2},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,1,1,1,0,1,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,1,1,1,1,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,1,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,1,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{2,1,1,1,1,1,1,1,1,2}
	};*/


	int mapData[mapMax][mapMax] = {//[11][2]
	{ 2, 2, 2, 2, 2, 2, 2, 2, 2 },
	{ 2, 0, 0, 0, 1, 0, 1, 0, 2 },
	{ 2, 0, 1, 0, 1, 0, 1, 0, 2 },
	{ 2, 0, 1, 0, 1, 0, 0, 0, 2 },
	{ 2, 0, 0, 0, 1, 0, 1, 0, 2 },
	{ 2, 0, 1, 0, 0, 0, 1, 0, 2 },
	{ 2, 0, 1, 0, 1, 0, 1, 3, 2 },
	{ 2, 0, 1, 0, 1, 1, 1, 2, 2 },
	{ 2, 0, 1, 0, 1, 0, 0, 0, 2 },
	{ 2, 0, 0, 0, 1, 1, 1, 0, 2 },
	{ 2, 0, 0, 0, 1, 0, 0, 0, 2 },
	{ 2, 2, 2, 2, 2, 2, 2, 2, 2 }
	};



	int tutoStageData[mapMax][mapMax] = {
		{2,2,2,2,2},
		{2,2,4,2,2},
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

	int stage1WallData[mapMax][mapMax] = {
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

	int stage2Wall[mapMax][mapMax] = {//[10][1]
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

	

	
	//サクライの落とし穴
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

	//ブロックを取れる回数
	int countPossBlock_ = 2;
};