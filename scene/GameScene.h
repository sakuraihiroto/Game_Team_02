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

	void DrawRemoveNum();

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
	
	static const uint32_t Digit = 2;		//桁数
	static const uint32_t Digit_num = 1;    //桁数(取り外し回数)

	//テクスチャハンドル
	uint32_t textureHundle_removeNum_ = 0;
	uint32_t textureHandle_reticle_ = 0; //レティクル
	uint32_t textureHandle_title_ = 0; //タイトル画像
	uint32_t textureHandle_gameclear_ = 0; //ゲームクリア画像
	uint32_t textureHandle_gameover_ = 0; //ゲームオーバー画像
	uint32_t textureHandleNumber_ = 0;
	uint32_t textureHandle_nextStage = 0;
	uint32_t textureHandle_tutorial_ = 0; //チュートリアル画像

	//スプライト
	Sprite* sprite_reticle = nullptr; //レティクル
	Sprite* sprite_background = nullptr;	//背景
	Sprite* sprite_THEBLOCK = nullptr;
	Sprite* sprite_tutorial = nullptr; //チュートリアル画像
	Sprite* spriteNumber[Digit] = {};		//時間
	Sprite* sprite_removeNum[Digit_num] = {}; //取り外し回数
	

	//3Dモデル
	Model* model_ = nullptr;
	Model* modelPlayer_ = nullptr;		//プレイヤーモデル
	Model* modelHand = nullptr;
	Sprite* sprite_title = nullptr; //タイトル画像
	Sprite* sprite_gameclear = nullptr; //ゲームクリア画像
	Sprite* sprite_gameover = nullptr; //ゲームオーバー画像
	Sprite* sprite_nextStage = nullptr;


	//サウンド
	uint32_t soundTitleBGM = 0; //タイトルBGM
	uint32_t soundTutorialBGM = 0; //チュートリアルBGM
	uint32_t soundPlayBGM_1 = 0; //プレイBGM(ステージ１)
	uint32_t soundPlayBGM_2 = 0; //プレイBGM(ステージ２)
	uint32_t soundGameOverBGM = 0; //ゲームオーバーBGM
	uint32_t soundClearBGM = 0; //クリアBGM
	//音声再生ハンドル
	uint32_t voiceTitleBGM = 0;
	uint32_t voiceTutorialBGM = 0;
	uint32_t voicePlayBGM_1 = 0;
	uint32_t voicePlayBGM_2 = 0;
	uint32_t voiceGameOverBGM = 0;
	uint32_t voiceClearBGM = 0;
	//サウンドフラグ 
	int soundFlag_title = 0;
	int soundFlag_tutorial = 0;
	int soundFlag_play_1 = 0;
	int soundFlag_play_2 = 0;
	int soundFlag_gameover = 0;
	int soundFlag_gameclear = 0;

	//ワールドトランスフォーム
	WorldTransform worldTransform_;
	//ビュープロジェクション
	ViewProjection viewProjection_;

	//自キャラ
	Player* player_ = nullptr;

	stageMap* stageMap_ = nullptr;

	char eachNumber[Digit] = {};
	char eachRemoveNum[Digit_num] = {};

	bool goalFlag = 0;

	bool pauseFlag = 0;

	
	Vector3 initializeWorldTransform_ = {};

	uint32_t stageBox = 0;
};