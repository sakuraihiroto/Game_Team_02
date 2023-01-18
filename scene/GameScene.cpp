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
	delete stageMap_;

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

	stageMap_ = new stageMap();
	//自キャラモデルの生成
	modelPlayer_ = Model::CreateFromOBJ("cube", true);
	//自キャラの初期化
	player_->Initialize(modelPlayer_, stageMap_);

	stageMap_->Initialize();


	//ワールドトランスフォームの初期化
	worldTransform_.Initialize();

	//viewProjection_.eye.y = -30;
	//viewProjection_.eye.z = -20;
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
		break;
	case gameOver:
		break;
	default:
		break;
	}
	//spaceでシーンチェンジ
	if (input_->TriggerKey(DIK_SPACE)&&scene<=gameScene)
	{
		scene += 1;
	}
	//gameOver&gameClearの時,titleに戻る
	else if(input_->TriggerKey(DIK_SPACE) && scene >gameScene)
	{
		scene = title;
	}
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
	debugText_->SetPos(20, 20);
	debugText_->Printf("scene:%d", scene);
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
