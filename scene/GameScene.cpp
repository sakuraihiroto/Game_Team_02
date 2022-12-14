#include "GameScene.h"
#include "TextureManager.h"
#include "matWorld.h"
#include <cassert>

MatWorld* matworld_ = nullptr;


GameScene::GameScene() {
}

GameScene::~GameScene() {
	delete model_;
	delete player_;
	delete stage_;
	delete modelStage_;

}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();

	////背景の生成
	//textureHandle_background = TextureManager::Load("background.png");
	//sprite_background = Sprite::Create(textureHandle_background, { 0,0 });

	//3Dモデルの生成
	model_ = Model::Create();

	//自キャラの生成
	player_ = new Player();
	//自キャラモデルの生成
	modelPlayer_ = Model::CreateFromOBJ("cube", true);
	//自キャラの初期化
	player_->Initialize(modelPlayer_);

	//ステージの生成
	stage_ = new Stage();
	//ステージモデルの生成
	modelStage_ = Model::CreateFromOBJ("stage_collar", true);
	//ステージの初期化
	stage_->Initialize(modelStage_);


	//ワールドトランスフォームの初期化
	worldTransform_.Initialize();

	//ビュープロジェクションの初期化
	viewProjection_.Initialize();

	//視点
	viewProjection_.eye.z = 40;
	viewProjection_.eye.y = 100;
	viewProjection_.fovAngleY = angle;

	//視点移動
	viewProjection_.UpdateMatrix();

}

void GameScene::Update() {

	stage_->Update();

}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>
	
	//背景描画
	//sprite_background->Draw();
	
	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	
	//ステージの描画
	stage_->Draw(viewProjection_);

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	

	// デバッグテキストの描画
	debugText_->DrawAll(commandList);
	//
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
