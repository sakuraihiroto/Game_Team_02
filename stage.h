#pragma once

#include "Model.h"
#include "WorldTransform.h"
#include "TextureManager.h"
#include "matWorld.h"
#include "Input.h"
#include "player.h"

class Stage
{

public:

	void Initialize(Model* model);

	void Update();

	void Draw(ViewProjection viewProjection);

private:

	//ワールド変換データ
	WorldTransform worldTransform_[2];
	
	//ビュープロジェクション
	ViewProjection viewProjection_;
	// 入力処理するため
	Input* input_ = nullptr;
	//モデル
	Model* model_ = nullptr;
	//プレイヤー
	Player* player_ = nullptr;

};

