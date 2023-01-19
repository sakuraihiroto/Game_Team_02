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

	//角度
	float playerDir = 0;

	bool deathFlag_ = false;
};
