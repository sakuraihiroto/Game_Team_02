#pragma once

#include "Model.h"
#include "WorldTransform.h"
#include "TextureManager.h"
#include "Input.h"
#include "matWorld.h"
#include"enemy.h"

class Stage
{

public:

	void Initialize(Model* model);

	void Update();

	void Draw(ViewProjection viewProjection);

	//ワールドトランスフォームを取得
	WorldTransform* GetWorldTransformPtr();
	WorldTransform GetWorldTransform();
	//
	Matrix4 GetMatWorld();
private:

	//ワールド変換データ
	WorldTransform worldTransform_;
	//ビュープロジェクション
	ViewProjection viewProjection_;
	// 入力処理するため
	Input* input_ = nullptr;
	//モデル
	Model* model_ = nullptr;
	//敵
	Enemy* enemy_ = nullptr;
};
