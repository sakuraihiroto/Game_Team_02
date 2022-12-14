#include "GameScene.h"
#include "TextureManager.h"
#include "matWorld.h"
#include <cassert>

MatWorld* matworld_ = nullptr;


GameScene::GameScene() {
}

GameScene::~GameScene() {
	delete player_;
	delete stage_;
	delete model_;
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

	//敵の生成,初期化
	std::unique_ptr<Enemy>newEnemy = std::make_unique<Enemy>();
	newEnemy->Initialize(model_, { 5,2,0 });
	//敵を登録する
	enemies_.push_back(std::move(newEnemy));

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

	//デスグラフが立った敵を削除
	enemies_.remove_if([](std::unique_ptr<Enemy>& enemy) {
		return enemy->IsDead();
		});
	player_->Update();
	stage_->Update();
	for (std::unique_ptr<Enemy>& enemy : enemies_)
	{
		enemy->Update();
	}
	//当たり判定
	Collision();
}

void GameScene::Collision()
{
	// 判定対象AとBとCの座標
	Vector3 posA, posB, posC, posD, posE;

	// AとBの距離
	float posAB = 0.0f;

	// 弾同士の半径
	float posR = 0.0f;
	float posR1 = 1.0f;
	float posR2 = 1.0f;

	// 自機リストの取得
	// 敵リストの取得
	const std::list<std::unique_ptr<Enemy>>& enemy = GetEnemies();
#pragma region 自機と敵の当たり判定
	for (std::unique_ptr<Enemy>& enemy : enemies_)
	{
		posA = player_->GetWorldPosition();
		posB = enemy->GetWorldPosition();

		posAB = (posB.x - posA.x) * (posB.x - posA.x) + (posB.y - posA.y) * (posB.y - posA.y) + (posB.z - posA.z) * (posB.z - posA.z);
		posR = (posR1 + posR2) * (posR1 + posR2);
		// 球と球の交差判定
		if (posAB <= posR)
		{
			// プレイヤーの衝突時コールバックを呼び出す
			//player_->OnCollision();
			// 敵弾の衝突時コールバックを呼び出す
			enemy->OnCollision();
		}
	}
#pragma endregion
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

	//プレイヤーの描画
	player_->Draw(viewProjection_);

	//敵の描画
	for (std::unique_ptr<Enemy>& enemy : enemies_)
	{
		enemy->Draw(viewProjection_);
	}

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
