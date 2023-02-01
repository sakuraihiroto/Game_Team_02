#include "GameScene.h"
#include "TextureManager.h"
#include "matWorld.h"
#include<math.h>
#include <cassert>

using Microsoft::WRL::ComPtr;
MatWorld* matworld_ = nullptr;


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
	for (int i = 0; i < 3; i++)
	{
		spriteNumber[i] = Sprite::Create(textureHandleNumber_, { 600.f + i * 40,0 });
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
	//modelHand = Model::CreateFromOBJ("hand", true);
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

		break;
	case gameOver:
		break;
	default:
		break;
	}
	//spaceでシーンチェンジ
	if (input_->TriggerKey(DIK_SPACE) && scene < gameScene)
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
	//sprite_background->Draw();
	// 

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
		spriteNumber[i]->SetTextureRect({ 40.0f*eachNumber[i],0}, {40,40});
		spriteNumber[i]->Draw();
	}
}