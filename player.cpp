#include "player.h"

// アフィン行列呼び出し
MatWorld* playerMatworld = nullptr;

void Player::Initialize(Model* model)
{
	// NULLポインタチェック
	assert(model);

	// 引数として受け取ったデータをメンバ変数に記録する
	model_ = model;

	// シングルトンインスタンスを取得する
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();

	// ワールド変換の初期化
	worldTransform_.Initialize();

	//ビュープロジェクションの初期化
	viewProjection_.Initialize();

}

//ワールド座標を入れる変数
Vector3 Player::GetWorldPosition()
{
	//ワールド座標を入れる変数
	Vector3 worldPos;
	//ワールド行列の平行移動分を取得
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

void Player::Update()
{

	//キャラクターの移動ベクトル
	Vector3 move = { 0, 0, 0 };

	//左方向
	if (input_->PushKey(DIK_A)) {
		leftMoveFlag = 1;
		rightMoveFlag = 0;
		upMoveFlag = 0;
		downMoveFlag = 0;
	}
	if (leftMoveFlag == 1)
	{
		move.x -= 0.2f;
	}
	//右方向
	if (input_->PushKey(DIK_D)) {
		rightMoveFlag = 1;
		leftMoveFlag = 0;
		downMoveFlag = 0;
		upMoveFlag = 0;
	}
	if (rightMoveFlag == 1)
	{
		move.x += 0.2f;
	}
	// 下方向
	if (input_->PushKey(DIK_S)) {
		downMoveFlag = 1;
		upMoveFlag = 0;
		rightMoveFlag = 0;
		leftMoveFlag = 0;
	}
	if (downMoveFlag == 1)
	{
		move.y -= 0.2f;
	}
	//上方向
	if (input_->PushKey(DIK_W)) {
		upMoveFlag = 1;
		downMoveFlag = 0;
		leftMoveFlag = 0;
		rightMoveFlag = 0;
	}
	if (upMoveFlag == 1)
	{
		move.y += 0.2f;
	}

	worldTransform_.translation_ += move;

	//行列の計算
	worldTransform_.matWorld_ = playerMatworld->CreateMatWorld(worldTransform_);
	//行列の転送
	worldTransform_.TransferMatrix();

}

//描画処理
void Player::Draw(ViewProjection& viewProjection_)
{
	model_->Draw(worldTransform_, viewProjection_);

	// デバックテキスト
	debugText_->SetPos(20, 80);
	debugText_->Printf(
		"leftMoveFlag(%d)",leftMoveFlag);
	// デバックテキスト
	debugText_->SetPos(20, 100);
	debugText_->Printf(
		"rightMoveFlag(%d)", rightMoveFlag);
	// デバックテキスト
	debugText_->SetPos(20, 120);
	debugText_->Printf(
		"upMoveFlag(%d)", upMoveFlag);
	// デバックテキスト
	debugText_->SetPos(20, 140);
	debugText_->Printf(
		"downMoveFlag(%d)", downMoveFlag);
}
