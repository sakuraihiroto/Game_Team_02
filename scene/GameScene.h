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

	/// <summary>
	/// 時間描画
	/// </summary>
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
		stage1,				//2
		stage2,				//3
		gameClear,			//4
		gameOver			//5
	};


	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	DebugText* debugText_ = nullptr;

	//テクスチャハンドル
	uint32_t textureHandle_background = 0;	//背景
	uint32_t HaveBlockHandle = 0;
	//シーン
	uint32_t scene = title;
	//タイム
	uint32_t time = 0;
	uint32_t count_ = 60;
	static const uint32_t Digit = 3;		//桁数

	//テクスチャハンドル
	uint32_t textureHandle_reticle_ = 0; //レティクル
	uint32_t textureHandle_title_ = 0; //タイトル画像
	uint32_t textureHandle_gameclear_ = 0; //ゲームクリア画像
	uint32_t textureHandle_gameover_ = 0; //ゲームオーバー画像
	uint32_t textureHandleNumber_ = 0;
	uint32_t textureHandle_nextStage = 0;
	//スプライト
	Sprite* sprite_reticle = nullptr; //レティクル
	Sprite* sprite_background = nullptr;	//背景
	Sprite* sprite_THEBLOCK = nullptr;
	Sprite* spriteNumber[Digit] = {};		//時間
	

	//3Dモデル
	Model* model_ = nullptr;
	Model* modelPlayer_ = nullptr;		//プレイヤーモデル
	Model* modelHand = nullptr;
	Sprite* sprite_title = nullptr; //タイトル画像
	Sprite* sprite_gameclear = nullptr; //ゲームクリア画像
	Sprite* sprite_gameover = nullptr; //ゲームオーバー画像
	Sprite* sprite_nextStage = nullptr;


	//ワールドトランスフォーム
	WorldTransform worldTransform_;
	//ビュープロジェクション
	ViewProjection viewProjection_;

	//自キャラ
	Player* player_ = nullptr;

	stageMap* stageMap_ = nullptr;

	char eachNumber[Digit] = {};

	bool goalFlag = 0;

	bool pauseFlag = 0;

	Vector3 initializeWorldTransform_ = {};
};