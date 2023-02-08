#include "GameScene.h"
#include "TextureManager.h"
#include "matWorld.h"
#include<math.h>
#include <cassert>

MatWorld* matworld_ = nullptr;

using Microsoft::WRL::ComPtr;


GameScene::GameScene() {
}

GameScene::~GameScene() {
	delete model_;
	delete player_;
	delete stageMap_;

}

void GameScene::Count()
{
	//カウントダウン
	count_--;
	//60フレーム毎に1秒減る
	if (count_ <= 0)
	{
		time -= 1;
		count_ = 50;
	}
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();

	//カウントダウン2Dスプライト
	textureHandleNumber_ = TextureManager::Load("bitmapfont.png");
	//取り外し回数のUI
	textureHundle_removeNum_ = TextureManager::Load("bitmapfont.png");
	//タイトル画像
	textureHandle_title_ = TextureManager::Load("title.png");
	sprite_title = Sprite::Create(textureHandle_title_, { 0,0 });
	//ゲームクリア画像
	textureHandle_gameclear_ = TextureManager::Load("gameclear.png");
	sprite_gameclear = Sprite::Create(textureHandle_gameclear_, { 0,0 });
	//ゲームオーバー画像
	textureHandle_gameover_ = TextureManager::Load("gameover.png");
	sprite_gameover = Sprite::Create(textureHandle_gameover_, { 0,0 });
	//チュートリアル画像
	textureHandle_tutorial_ = TextureManager::Load("tutorial.png");
	sprite_tutorial = Sprite::Create(textureHandle_tutorial_, { 0,0 });

	//サウンドデータの読み込み
	soundTitleBGM = audio_->LoadWave("Audio/title.mp3"); //タイトルBGM
	soundTutorialBGM = audio_->LoadWave("Audio/tutorial.mp3"); //チュートリアルBGM
	soundPlayBGM_1 = audio_->LoadWave("Audio/play_1.mp3"); //プレイBGM st1
	soundPlayBGM_2 = audio_->LoadWave("Audio/play_2.mp3"); //プレイBGM st2
	soundGameOverBGM = audio_->LoadWave("Audio/game_over.mp3"); //ゲームオーバーBGM
	soundClearBGM = audio_->LoadWave("Audio/game_clear.mp3"); //クリアBGM
	

	for (int i = 0; i < 2; i++)
	{
		spriteNumber[i] = Sprite::Create(textureHandleNumber_, { 900.f + i * 80,0 });
	}

	for (int i = 0; i < 1; i++)
	{
		sprite_removeNum[i] = Sprite::Create(textureHundle_removeNum_, { 1500.0f,i * 10.0f });
	}

	
	//レティクル(2D)
	textureHandle_reticle_ = TextureManager::Load("reticle.png");
	sprite_reticle = Sprite::Create(textureHandle_reticle_, { 300,200 });

	//時間
	time = 60;

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

	//ビュープロジェクションの初期化
	viewProjection_.Initialize();

	//視点移動
	viewProjection_.UpdateMatrix();

	
}

void GameScene::Update() {

	switch (stageMap_->iswhereStage_)
	{
	case title://////////タイトル//////////

		
		////ゲームオーバーBGM停止
		//soundFlag_gameover = 0;
		//audio_->StopWave(voiceGameOverBGM);

		////ゲームクリアBGM停止
		//soundFlag_gameclear = 0;
		//audio_->StopWave(voiceClearBGM);

		//タイトルBGM再生
		if (soundFlag_title == 0)
		{
			voiceTitleBGM = audio_->PlayWave(soundTitleBGM, true);

			soundFlag_title = 1;
		}

		if (input_->PushKey(DIK_SPACE))
		{
			stageMap_->iswhereStage_++;
		}

		


		break;
	case tutorial://////////チュートリアル//////////

		//タイトルBGM停止
		soundFlag_title = 0;
		audio_->StopWave(voiceTitleBGM);

		//ゲームオーバーBGM停止
		soundFlag_gameover = 0;
		audio_->StopWave(voiceGameOverBGM);

		//チュートリアルBGM再生
		if (soundFlag_tutorial == 0)
		{
			voiceTutorialBGM = audio_->PlayWave(soundTutorialBGM, true);

			soundFlag_tutorial = 1;
		}

		player_->Update();
		stageMap_->Update();
	
		//カメラ追従
		viewProjection_.eye.x = player_->GetX();
		viewProjection_.eye.y = player_->GetY();
		viewProjection_.eye.z = player_->GetZ();

		viewProjection_.target.x = viewProjection_.eye.x - cos(player_->GetPlayerDir()) * 8;
		viewProjection_.target.y = player_->GetY();
		viewProjection_.target.z = viewProjection_.eye.z - sin(player_->GetPlayerDir()) * 8;

		//リセット
		if (input_->PushKey(DIK_R))
		{
			stageMap_->ResetStage();
			player_->ResetPlayer();
			time = 60;
			count_ = 50;
			goalFlag = 0;
			pauseFlag = 0;
		}

		//落とし穴に落ちたらゲームオーバー
		if (stageMap_->GethollFlag() == 1)
		{
			stageMap_->iswhereStage_ = gameOver;
			downStageflag = 1;
		}

		break;


	case stage1://////////ステージ１//////////

		//チュートリアルBGM停止
		soundFlag_tutorial = 0;
		audio_->StopWave(voiceTutorialBGM);

		//ゲームオーバーBGM停止
		soundFlag_gameover = 0;
		audio_->StopWave(voiceGameOverBGM);

		//プレイ１BGM再生
		if (soundFlag_play_1 == 0)
		{
			voicePlayBGM_1 = audio_->PlayWave(soundPlayBGM_1, true);

			soundFlag_play_1 = 1;
		}

		player_->Update();
		stageMap_->Update();
		//カウントダウン
		Count();

		//カメラ追従
		viewProjection_.eye.x = player_->GetX();
		viewProjection_.eye.y = player_->GetY();
		viewProjection_.eye.z = player_->GetZ();

		viewProjection_.target.x = viewProjection_.eye.x - cos(player_->GetPlayerDir()) * 8;
		viewProjection_.target.y = viewProjection_.eye.y - tan(player_->GetPlayerDirY()) * 8;
		viewProjection_.target.z = viewProjection_.eye.z - sin(player_->GetPlayerDir()) * 8;



		////下向き
		//if (input_->PushKey(DIK_DOWN))
		//{
		//	viewProjection_.target.y = player_->GetY() - 3.5f;
		//}

		//リセット
		if (input_->PushKey(DIK_R))
		{
			stageMap_->ResetStage();
			player_->ResetPlayer();
			time = 60;
			count_ = 50;
			goalFlag = 0;
			pauseFlag = 0;
		}

		//タイマーが0になったらゲームオーバー
		if (time == 0)
		{
			stageMap_->iswhereStage_ = gameOver;
			downStageflag = 2;
		}

		//落とし穴に落ちたらゲームオーバー
		if (stageMap_->GethollFlag() == 1)
		{
			stageMap_->iswhereStage_ = gameOver;
			downStageflag = 2;
		}

		break;

	case stage2: //////////ステージ2//////////

		//プレイ１BGM停止
		soundFlag_play_1 = 0;
		audio_->StopWave(voicePlayBGM_1);

		//ゲームオーバーBGM停止
		soundFlag_gameover = 0;
		audio_->StopWave(voiceGameOverBGM);

		//プレイ2BGM再生
		if (soundFlag_play_2 == 0)
		{
			voicePlayBGM_2 = audio_->PlayWave(soundPlayBGM_2, true);

			soundFlag_play_2 = 1;
		}

		player_->Update();
		stageMap_->Update();
		//カウントダウン
		Count();

		//カメラ追従
		viewProjection_.eye.x = player_->GetX();
		viewProjection_.eye.y = player_->GetY();
		viewProjection_.eye.z = player_->GetZ();

		viewProjection_.target.x = viewProjection_.eye.x - cos(player_->GetPlayerDir()) * 8;
		viewProjection_.target.y = viewProjection_.eye.y - tan(player_->GetPlayerDirY()) * 8;
		viewProjection_.target.z = viewProjection_.eye.z - sin(player_->GetPlayerDir()) * 8;

		////下向き
		//if (input_->PushKey(DIK_DOWN))
		//{
		//	viewProjection_.target.y = player_->GetY() - 3.5f;
		//}

		//リセット
		if (input_->PushKey(DIK_R))
		{
			stageMap_->ResetStage();
			player_->ResetPlayer();
			time = 60;
			count_ = 50;
			goalFlag = 0;
			pauseFlag = 0;
		}

		//タイマーが0になったらゲームオーバー
		if (time == 0)
		{
			stageMap_->iswhereStage_ = gameOver;
			downStageflag = 3;
		}

		//落とし穴に落ちたらゲームオーバー
		if (stageMap_->GethollFlag() == 1)
		{
			stageMap_->iswhereStage_ = gameOver;
			downStageflag = 3;
		}

	case gameOver://////////ゲームオーバー//////////

		//チュートリアルBGM停止
		soundFlag_tutorial = 0;
		audio_->StopWave(voiceTutorialBGM);

		//プレイ１BGM停止
		soundFlag_play_1 = 0;
		audio_->StopWave(voicePlayBGM_1);

		//プレイ2BGM停止
		soundFlag_play_2 = 0;
		audio_->StopWave(voicePlayBGM_2);

		//ゲームオーバーBGM再生
		if (soundFlag_gameover == 0)
		{
			voiceGameOverBGM = audio_->PlayWave(soundGameOverBGM, true);

			soundFlag_gameover = 1;
		}

		//初期化処理
		stageMap_->ResetStage();
		player_->ResetPlayer();
		time = 60;
		count_ = 50;
		goalFlag = 0;
		pauseFlag = 0;

		//チュートリアルで死んだら
		if (input_->TriggerKey(DIK_R) && downStageflag == 1)
		{
			stageMap_->iswhereStage_ = tutorial;
			downStageflag = 0;
		}
		//ステージ1で死んだら
		if (input_->TriggerKey(DIK_R) && downStageflag == 2)
		{
			stageMap_->iswhereStage_ = stage1;
			downStageflag = 0;
		}
		//ステージ2で死んだら
		if (input_->TriggerKey(DIK_R) && downStageflag == 3)
		{
			stageMap_->iswhereStage_ = stage2;
			downStageflag = 0;
		}

		break;
	case gameClear://////////ゲームクリア//////////

		//プレイ2BGM停止
		soundFlag_play_2 = 0;
		audio_->StopWave(voicePlayBGM_2);

		//プレイ2BGM再生
		if (soundFlag_gameclear == 0)
		{
			voiceClearBGM = audio_->PlayWave(soundClearBGM, true);

			soundFlag_gameclear = 1;
		}

		//初期化処理
		stageMap_->ResetStage();
		player_->ResetPlayer();
		time = 60;
		count_ = 50;
		goalFlag = 0;
		pauseFlag = 0;
		downStageflag = 0;
		break;
	}

	if (input_->TriggerKey(DIK_SPACE) && (stageMap_->iswhereStage_ == gameOver || stageMap_->iswhereStage_ == gameClear))
	{
		stageMap_->iswhereStage_ = title;
	}

	//行列を更新する
	viewProjection_.UpdateMatrix();
}

void GameScene::DrawTime()
{

	//各桁の数値を描画
	for (int i = 0; i < Digit; i++)
	{
		//各桁の値を取り出す
		int number = time;

		int CalcDigit = 10;
		for (int i = 0; i < Digit; i++)
		{
			eachNumber[i] = number / CalcDigit;
			number = number % CalcDigit;
			CalcDigit = CalcDigit / 10;
		}
		spriteNumber[i]->SetSize({ 80,80 });
		spriteNumber[i]->SetTextureRect({ 80.0f * eachNumber[i],0 }, { 80,80 });
		spriteNumber[i]->Draw();
	}
}

//取り外し回数の関数
void GameScene::DrawRemoveNum()
{
	//各桁の数値を描画
	for (int i = 0; i < Digit_num; i++)
	{
		//各桁の値を取り出す
		int number = stageMap_->countPossBlock_;

		int CalcDigit = 1;
		for (int i = 0; i < Digit_num; i++)
		{
			eachRemoveNum[i] = number / CalcDigit;
			number = number % CalcDigit;
			CalcDigit = CalcDigit / 1;
		}
		sprite_removeNum[i]->SetSize({ 80,80 });
		sprite_removeNum[i]->SetTextureRect({ 80.0f * eachRemoveNum[i],0 }, { 80,80 });
		sprite_removeNum[i]->Draw();
	}
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
	
	

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList.Get());
	
	
	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
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

	

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList.Get());

	//タイトル
	if (stageMap_->iswhereStage_ == title)
	{
		sprite_title->Draw();
	}
	//チュートリアル
	if (stageMap_->iswhereStage_ == tutorial)
	{
		sprite_tutorial->Draw();
		//プレイヤーの手
		stageMap_->DrawHand();
		//取り外しUI
		DrawRemoveNum();
		//レティクル
		sprite_reticle->Draw();
	}
	//ゲーム画面(ステージ1)
	if (stageMap_->iswhereStage_ == stage1)
	{
		//プレイヤーの手
		stageMap_->DrawHand();
		//時間を描画
		DrawTime();
		//取り外しUI
		DrawRemoveNum();
		//レティクル
		sprite_reticle->Draw();
	}
	//ゲーム画面(ステージ2)
	if (stageMap_->iswhereStage_ == stage2)
	{
		//プレイヤーの手
		stageMap_->DrawHand();
		//時間を描画
		DrawTime();
		//取り外しUI
		DrawRemoveNum();
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


	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	

	// デバッグテキストの描画
	debugText_->DrawAll(commandList.Get());
	
	debugText_->SetPos(20, 20);
	debugText_->Printf("scene:%d", stageMap_->iswhereStage_);
	debugText_->SetPos(20, 40);
	debugText_->Printf("count:%d", count_);
	debugText_->SetPos(20, 0);
	debugText_->Printf("scene:%d", stageMap_->iswhereStage_);
	debugText_->SetPos(20, 200);
	debugText_->Printf("soundFlag_title:%d", soundFlag_title);
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

