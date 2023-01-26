﻿#pragma once
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

	bool Collision(float px, float pz);

	bool CollisionHoll(float px, float pz);

	void DeleteBlock(float px, float pz);

	void PutBlock(float px, float pz);

	void ResetStage();
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
		Floor,			//ブロック
		Holl,			//落とし穴
		FilledFloor		//埋めたフロア(生成には関係なし)
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


	/*int stage1Wall[mapMax][mapMax] = {
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

	int stage1Wall[mapMax][mapMax] = {//[10][1]
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

	/*int floorData[mapMax][mapMax] = {
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,1,0,1,0,0,0,0},
		{0,0,0,1,0,1,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0}
	};*/
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

	/*int stage1Floor[mapMax][mapMax] = {
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,1,0,1,0,0,0,0},
		{0,0,0,1,0,1,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0}
	};*/
	//サクライの落とし穴
	int stage1Floor[mapMax][mapMax] = {
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


	MatWorld* matWorld_ = nullptr;

	// デバッグテキスト
	DebugText* debugText_ = nullptr;

	// 入力処理するため
	Input* input_ = nullptr;

	//取ったブロックを所持しているか
	int possFlag_ = 0;

	//ブロックを取れる回数
	int countPossBlock_ = 2;
};