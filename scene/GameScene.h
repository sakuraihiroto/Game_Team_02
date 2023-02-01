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

	void DrawTime();

	/// <summary>
	/// カウントダウン
	/// </summary>
	void Count();

private: // メンバ変数
	enum シーン
	{
		title,				//0
		tutorial,			//1
		gameScene,			//2
		gameOver,			//3
		gameClear			//4
	};


	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	DebugText* debugText_ = nullptr;

	//テクスチャハンドル
	uint32_t textureHandleNumber_ = 0;
	uint32_t textureHandle_hand_ = 0; //プレイヤーの手
	uint32_t textureHandle_reticle_ = 0; //レティクル
	uint32_t textureHandle_title_ = 0; //タイトル画像
	uint32_t textureHandle_gameclear_ = 0; //ゲームクリア画像
	uint32_t textureHandle_gameover_ = 0; //ゲームオーバー画像

	//シーン
	uint32_t scene = title;
	//タイム
	uint32_t time = 0;
	uint32_t count_ = 60;
	
	static const uint32_t Digit = 3;		//桁数

	//スプライト
	Sprite* spriteNumber[Digit] = {};		//時間
	Sprite* sprite_hand = nullptr; //プレイヤーの手
	Sprite* sprite_reticle = nullptr; //レティクル
	Sprite* sprite_title = nullptr; //タイトル画像
	Sprite* sprite_gameclear = nullptr; //ゲームクリア画像
	Sprite* sprite_gameover = nullptr; //ゲームオーバー画像

	//3Dモデル
	Model* model_ = nullptr;
	Model* modelPlayer_ = nullptr; //プレイヤーモデル


	//ワールドトランスフォーム
	WorldTransform worldTransform_;
	//ビュープロジェクション
	ViewProjection viewProjection_;

	//自キャラ
	Player* player_ = nullptr;

	stageMap* stageMap_ = nullptr;
};