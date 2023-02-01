﻿#include "GameScene.h"
#include "TextureManager.h"
#include "matWorld.h"
#include<math.h>
#include <cassert>

MatWorld* matworld_ = nullptr;

using Microsoft::WRL::ComPtr;


GameScene::GameScene() {
}

GameScene::~GameScene() {
	delete model_;
	delete player_;
	delete stageMap_;

}

void GameScene::Count()
{
	//カウントダウン
	count_--;
	//60フレーム毎に1秒減る
	if (count_ <= 0)
	{
		time -= 1;
		count_ = 60;
	}
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();

	//カウントダウン2Dスプライト
	textureHandleNumber_ = TextureManager::Load("bitmapfont.png");

	//タイトル画像
	textureHandle_title_ = TextureManager::Load("title.png");
	sprite_title = Sprite::Create(textureHandle_title_, { 0,0 });
	//ゲームクリア画像
	textureHandle_gameclear_ = TextureManager::Load("gameclear.png");
	sprite_gameclear = Sprite::Create(textureHandle_gameclear_, { 0,0 });
	//ゲームオーバー画像
	textureHandle_gameover_ = TextureManager::Load("gameover.png");
	sprite_gameover = Sprite::Create(textureHandle_gameover_, { 0,0 });

	

	for (int i = 0; i < 3; i++)
	{
		spriteNumber[i] = Sprite::Create(textureHandleNumber_, { 600.f + i * 40,0 });
	}

	//プレイヤーの手(2D)
	textureHandle_hand_ = TextureManager::Load("hand.png");
	sprite_hand = Sprite::Create(textureHandle_hand_, { 700,350 });
	//レティクル(2D)
	textureHandle_reticle_ = TextureManager::Load("reticle.png");
	sprite_reticle = Sprite::Create(textureHandle_reticle_, { 330,220 });

	//時間
	time = 160;

	//3Dモデルの生成
	model_ = Model::Create();

	//自キャラの生成
	player_ = new Player();

	stageMap_ = new stageMap();
	//自キャラモデルの生成
	modelPlayer_ = Model::CreateFromOBJ("cube", true);
	//自キャラの初期化
	player_->Initialize(modelPlayer_, stageMap_);


	stageMap_->Initialize();

	//ワールドトランスフォームの初期化
	worldTransform_.Initialize();

	//ビュープロジェクションの初期化
	viewProjection_.Initialize();

	//視点移動
	viewProjection_.UpdateMatrix();

	
}

void GameScene::Update() {

	switch (scene)
	{
	case title:

		break;
	case tutorial:
		break;
	case gameScene:
		player_->Update();
		//カウントダウン
		Count();

		//カメラ追従
		viewProjection_.eye.x = player_->GetX();
		viewProjection_.eye.y = player_->GetY();
		viewProjection_.eye.z = player_->GetZ();

		viewProjection_.target.x = viewProjection_.eye.x - cos(player_->GetPlayerDir()) * 8;
		viewProjection_.target.y = player_->GetY();
		viewProjection_.target.z = viewProjection_.eye.z - sin(player_->GetPlayerDir()) * 8;

		//下向き
		if (input_->PushKey(DIK_DOWN))
		{
			viewProjection_.target.y = player_->GetY() - 3.5f;
		}

		//リセット
		if (input_->PushKey(DIK_R))
		{
			stageMap_->ResetStage();
			time = 160;
			count_ = 60;

		}

		break;
	case gameOver:
		break;
	default:
		break;
	}
	//spaceでシーンチェンジ
	if (input_->TriggerKey(DIK_SPACE) && scene <= gameScene)
	{
		scene += 1;
	}
	//gameOver&gameClearの時,titleに戻る
	else if (input_->TriggerKey(DIK_SPACE) && scene > gameScene)
	{
		scene = title;
	}

	//行列を更新する
	viewProjection_.UpdateMatrix();
}

void GameScene::DrawTime()
{

	//各桁の数値を描画
	for (int i = 0; i < Digit; i++)
	{
		spriteNumber[i]->SetSize({ 40,40 });
		spriteNumber[i]->SetTextureRect({ 0,0 }, { 40,40 });
		spriteNumber[i]->Draw();
		//各桁の値を取り出す
		char eachNumber[Digit] = {};
		int number = time;


		int CalcDigit = 100;
		for (int i = 0; i < Digit; i++)
		{
			eachNumber[i] = number / CalcDigit;
			number = number % CalcDigit;
			CalcDigit = CalcDigit / 10;
		}
		spriteNumber[i]->SetSize({ 40,40 });
		spriteNumber[i]->SetTextureRect({ 40.0f * eachNumber[i],0 }, { 40,40 });
		spriteNumber[i]->Draw();
	}
}

void GameScene::Draw() {

	// コマンドリストの取得
	ComPtr<ID3D12GraphicsCommandList> commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList.Get());

	

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>
	
	

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList.Get());
	
	
	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	switch (scene)
	{
	case title:
		break;
	case tutorial:
		break;
	case gameScene:
		//プレイヤーの描画
		player_->Draw(viewProjection_);
		stageMap_->Draw(viewProjection_);
		
		break;
	case gameOver:
		break;
	default:
		break;
	}

	

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList.Get());

	//タイトル
	if (scene == title)
	{
		sprite_title->Draw();
	}
	//ゲーム画面
	if (scene == gameScene)
	{
		//時間を描画
		DrawTime();
		//プレイヤーの手
		sprite_hand->Draw();
		//レティクル
		sprite_reticle->Draw();
	}
	//ゲームクリア
	if (scene == gameClear)
	{
		sprite_gameclear->Draw();
	}
	//ゲームオーバー
	if (scene == gameOver)
	{
		sprite_gameover->Draw();
	}


	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	

	// デバッグテキストの描画
	debugText_->DrawAll(commandList.Get());
	
	debugText_->SetPos(20, 20);
	debugText_->Printf("scene:%d", scene);
	debugText_->SetPos(20, 40);
	debugText_->Printf("count:%d", count_);
	debugText_->SetPos(20, 60);
	debugText_->Printf("time:%d", time);
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

