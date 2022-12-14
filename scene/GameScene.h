#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "DebugText.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "player.h"
#include "stage.h"
#include "enemy.h"
#include<memory>//ユニークポインタ
#include<list>


/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
  /// <summary>
  /// コンストクラタ
  /// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// 衝突判定
	/// </summary>
	void Collision();

	// 弾リストを取得
	const std::list < std::unique_ptr<Enemy>>& GetEnemies() { return enemies_; }

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	DebugText* debugText_ = nullptr;

	//テクスチャハンドル
	uint32_t textureHandle_background = 0; //背景

	//スプライト
	Sprite* sprite_background = nullptr; //背景

	//敵
	std::list<std::unique_ptr<Enemy>>enemies_;
	Enemy* enemy_ = nullptr;

	//3Dモデル
	Model* model_ = nullptr;
	Model* modelPlayer_ = nullptr; //プレイヤーモデル
	Model* modelStage_ = nullptr;  //ステージモデル

	//ワールドトランスフォーム
	WorldTransform worldTransform_;
	//ビュープロジェクション
	ViewProjection viewProjection_;

	//自キャラ
	Player* player_ = nullptr;
	//ステージ
	Stage* stage_ = nullptr;

	//視野角
	float angle = 0.5f;

};