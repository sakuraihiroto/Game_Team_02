#include "GameScene.h"
#include "TextureManager.h"
#include "matWorld.h"
#include<math.h>
#include <cassert>

using Microsoft::WRL::ComPtr;
MatWorld* matworld_ = nullptr;

 bool Player::nextStageFlag ;

GameScene::GameScene() {
}

GameScene::~GameScene() {
	delete model_;
	delete player_;
	delete stageMap_;

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
	//nextstage画像
	textureHandle_nextStage = TextureManager::Load("nextstage.png");
	sprite_nextStage= Sprite::Create(textureHandle_nextStage, { 0,0 });
	//レティクル(2D)
	textureHandle_reticle_ = TextureManager::Load("reticle.png");
	sprite_reticle = Sprite::Create(textureHandle_reticle_, { 320,200 });

	for (int i = 0; i < 3; i++)
	{
		spriteNumber[i] = Sprite::Create(textureHandleNumber_, { 600.0f + i * 40,0.0f });
	}
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

	//マップの初期化
	stageMap_->Initialize();

	//ワールドトランスフォームの初期化
	worldTransform_.Initialize();

	//ビュープロジェクションの初期化
	viewProjection_.Initialize();

	//視点移動
	viewProjection_.UpdateMatrix();
}

void GameScene::Update() {

	switch (stageMap_->iswhereStage_)
	{
	case title:
		if (input_->PushKey(DIK_SPACE))
		{
			stageMap_->iswhereStage_ = 0;
			stageMap_->iswhereStage_++;
			stageMap_->pauseFlag_ = 0;

			initializeWorldTransform_.x = player_->GetX();
			initializeWorldTransform_.z = player_->GetZ();

			initializeWorldTransform_.x = -3;
			initializeWorldTransform_.z = -4;

			player_->SetX(initializeWorldTransform_.x);
			player_->SetZ(initializeWorldTransform_.z);

		}
		break;
	case tutorial:
		
		player_->Update();
		stageMap_->Update();
		//カウントダウン
		Count();

		//カメラ追従
		viewProjection_.eye.x = player_->GetX();
		viewProjection_.eye.y = player_->GetY();
		viewProjection_.eye.z = player_->GetZ();

		viewProjection_.target.x = viewProjection_.eye.x - cos(player_->GetPlayerDir()) * 8;
		viewProjection_.target.y = player_->GetY();
		viewProjection_.target.z = viewProjection_.eye.z - sin(player_->GetPlayerDir()) * 8;
		break;
	case stage1:
		
		player_->Update();
		stageMap_->Update();
		//カウントダウン
		Count();

		//カメラ追従
		viewProjection_.eye.x = player_->GetX();
		viewProjection_.eye.y = player_->GetY();
		viewProjection_.eye.z = player_->GetZ();

		viewProjection_.target.x = viewProjection_.eye.x - cos(player_->GetPlayerDir()) * 8;
		viewProjection_.target.y = player_->GetY();
		viewProjection_.target.z = viewProjection_.eye.z - sin(player_->GetPlayerDir()) * 8;
		break;
	case stage2:
		
		player_->Update();
		stageMap_->Update();
		//カウントダウン
		Count();

		//カメラ追従
		viewProjection_.eye.x = player_->GetX();
		viewProjection_.eye.y = player_->GetY();
		viewProjection_.eye.z = player_->GetZ();

		viewProjection_.target.x = viewProjection_.eye.x - cos(player_->GetPlayerDir()) * 8;
		viewProjection_.target.y = player_->GetY();
		viewProjection_.target.z = viewProjection_.eye.z - sin(player_->GetPlayerDir()) * 8;

		break;
	case gameClear:
		break;
	case gameOver:
		break;
	default:
		break;
	}

	//stageMap_->SetPauseFlag(pauseFlag);
	////spaceでシーンチェンジ
	//if (input_->TriggerKey(DIK_SPACE) && scene==title||pauseFlag==0)
	//{
	//	//scene += 1;
	//	//シーンを取得
	//	stageMap_->GetScene(scene);
	//	player_->GetScene(scene);
	//	//stageを変える
	//	stageMap_->ChangeMap();
	//	pauseFlag == true;
	//}

	//ゴール処理


	/*if (stageMap_->SetGoal(goalFlag))
	{
		scene += 1;
		goalFlag = 0;
	}*/


	//gameOver&gameClearの時,titleに戻る
	

	//行列を更新する
	viewProjection_.UpdateMatrix();
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
	//背景描画
	

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList.Get());
	debugText_->SetPos(20, 20);
	debugText_->Printf("scene:%d", scene);
	debugText_->SetPos(20, 40);
	debugText_->Printf("count:%d", count_);
	debugText_->SetPos(20, 60);
	debugText_->Printf("time:%d", time);
	switch (stageMap_->iswhereStage_)
	{
	case title:
		break;
	case tutorial:
		//プレイヤーの描画
		player_->Draw(viewProjection_);
		stageMap_->Draw(viewProjection_);
		break;
	case stage1:
		//プレイヤーの描画
		player_->Draw(viewProjection_);
		stageMap_->Draw(viewProjection_);
		break;
	case stage2:
		//プレイヤーの描画
		player_->Draw(viewProjection_);
		stageMap_->Draw(viewProjection_);
		break;
	case gameOver:
		break;
	default:
		break;
	}
	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>


	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList.Get());

	
	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>
//sprite_THEBLOCK->Draw();
//タイトル
if (stageMap_->iswhereStage_ == title)
{
	sprite_title->Draw();
}
//ゲーム画面
if (stageMap_->iswhereStage_ == stage2)
{
	//プレイヤーの手
	//stageMap_->DrawHand();
	//時間を描画
	DrawTime();
	//レティクル
	sprite_reticle->Draw();
}
//ゲームクリア
if (stageMap_->iswhereStage_ == gameClear)
{
	sprite_gameclear->Draw();
}
//ゲームオーバー
if (stageMap_->iswhereStage_ == gameOver)
{
	sprite_gameover->Draw();
}

if (player_->nextStageFlag)
{
	sprite_nextStage->Draw();
}

	//時間を描画
	DrawTime();

	// デバッグテキストの描画
	debugText_->DrawAll(commandList.Get());
	//
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
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
	//リセット
	if (input_->TriggerKey(DIK_R))
	{
		time = 160;
	}
}

void GameScene::DrawTime()
{

	//各桁の数値を描画
	for (int i = 0; i < Digit; i++)
	{
		//各桁の値を取り出す
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