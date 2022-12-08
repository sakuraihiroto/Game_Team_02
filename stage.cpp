#include "stage.h"
#include <cassert>

MatWorld* stageMatworld = nullptr;

void Stage::Initialize(Model* model)
{
	assert(model);

	model_ = model;
	worldTransform_.Initialize();

	//s—ñ‚ÌŒvŽZ
	worldTransform_.matWorld_ = stageMatworld->CreateMatWorld(worldTransform_);
	//s—ñ‚Ì“]‘—
	worldTransform_.TransferMatrix();
}

void Stage::Update()
{

}

void Stage::Draw(ViewProjection viewProjection_)
{
	model_->Draw(worldTransform_, viewProjection_);
}

