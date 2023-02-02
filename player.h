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

//追加分-------------------------
#include <Windows.h>

class Player
{
public:
	void Initialize(Model* model, stageMap* stageMap);

	///<summary>
	///更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(ViewProjection& viewProjection_);

	//ワールド座標を取得
	Vector3 GetWorldPosition();

	//プレイヤーの座標
	float GetX() { return worldTransform_.translation_.x; }
	float GetY() { return worldTransform_.translation_.y; }
	float GetZ() { return worldTransform_.translation_.z; }

	float GetPlayerDir() { return playerDir; }

	//追加分-------------------------

	float GetPlayerDirY() { return playerDirY; }

	//追加終わり-------------------------

private:

	// ワールド変換データ
	WorldTransform worldTransform_;
	//ビュープロジェクション
	ViewProjection viewProjection_;
	// モデル
	Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;
	// デバッグテキスト
	DebugText* debugText_ = nullptr;
	// 入力処理するため
	Input* input_ = nullptr;

	stageMap* stageMap_ = nullptr;

	//速度
	Vector3 velocity_;

	//角度 前向き
	float playerDir = 0;

	//追加分-------------------------

	float playerDirY = 0;
	int deathFlag_ = 0;

	//追加終わり-------------------------
	
	//プレイヤー初期位置
	uint32_t x = 1;
	uint32_t y = 10;


	//追加分-------------------------

	POINT mousePos_ = { 0,0 };
	POINT mousePrePos_ = {0,0};

	//追加終わり-------------------------
};