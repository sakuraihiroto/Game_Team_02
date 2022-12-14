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

	//キャラクターの移動ベクトル
	Vector3 move = { 0,2,0 };//座標{x,y,z}

	//初期座標をセット
	worldTransform_.translation_ = move;

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

}

//描画処理
void Player::Draw(ViewProjection& viewProjection_,WorldTransform worldTransform)
{
	
	//// デバックテキスト
	//debugText_->SetPos(20, 80);
	//debugText_->Printf(
	//	"leftMoveFlag(%d)",leftMoveFlag);
	//// デバックテキスト
	//debugText_->SetPos(20, 100);
	//debugText_->Printf(
	//	"rightMoveFlag(%d)", rightMoveFlag);
	//// デバックテキスト
	//debugText_->SetPos(20, 120);
	//debugText_->Printf(
	//	"upMoveFlag(%d)", upMoveFlag);
	//// デバックテキスト
	//debugText_->SetPos(20, 140);
	//debugText_->Printf(
	//	"downMoveFlag(%d)", downMoveFlag);
}
