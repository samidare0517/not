#include "GameExplanation.h"
#include "KeyExplanationScene.h"
#include "InputState.h"
#include "SceneManager.h"
#include "PauseScene.h"
#include "TitleScene.h"
#include "KeyGameOverScene.h"
#include <time.h>		// ランダム用
#include "DxLib.h"

void GameExplanation::FadeInUpdate(const InputState& input)
{
	fadeValue = fadeTimer;
	if (--fadeTimer == 0)
	{
		updateFunc = &GameExplanation::NormalUpdate;
		fadeValue = 0;
	}
}

void GameExplanation::NormalUpdate(const InputState& input)
{
	// 次へボタンが押されたら次のシーンへ移行する
	if (input.IsTriggred(InputType::RBbutton))
	{
		// SEの音量を調整する
		ChangeVolumeSoundMem(255 * 60 / 100, seButton);

		// SEを呼び出す
		PlaySoundMem(seButton, DX_PLAYTYPE_BACK, false);

		updateFunc = &GameExplanation::FadeOutUpdate;
	}
}

void GameExplanation::FadeOutUpdate(const InputState& input)
{
	fadeValue = static_cast<int>(255 * (static_cast<float>(fadeTimer) / static_cast<float>(fadeIntarval)));
	if (++fadeTimer == fadeIntarval)
	{
		manager_.CangeScene(new TitleScene(manager_));
		return;
	}
}

GameExplanation::GameExplanation(SceneManager& manager) : Scene(manager),
updateFunc(&GameExplanation::FadeInUpdate)
{
	// 画像のロード
	explanationHandle = LoadGraph("data/KeyGameSetumei.png");
	buttonRBHandle = LoadGraph("data/button/buttonRB.png");
	gameScreenHanadle = LoadGraph("data/gamesene.png");

	// SEの読み込み
	seButton = LoadSoundMem("data/BGM/NextSE.mp3");
}

GameExplanation::~GameExplanation()
{
	// 画像のデリート
	DeleteGraph(explanationHandle);
	DeleteGraph(buttonRBHandle);

	// 音楽のデリート
	DeleteSoundMem(seButton);
}

void GameExplanation::Update(const InputState& input)
{
	(this->*updateFunc)(input);
}

void GameExplanation::Draw()
{
	// 背景描画
	DrawGraph(0, 0, explanationHandle, true);
	DrawGraph(1100, 825, buttonRBHandle, true);
	DrawGraph(670, 580, gameScreenHanadle, true);

	// テスト用座標固定アニメーション
	//DrawRectRotaGraph(200, 200,
	//	left, top, rigth, bottom,
	//	1, 0, starHandle1, true, false);

	// ランダムになっているか(デバック用)
//	DrawFormatString(0, 200, GetColor(255, 255, 255), "星:% d\n", starnum);
	// フレーム数(デバック用)
//	DrawFormatString(0, 300, GetColor(255, 255, 255), "フレーム:% d\n", frameCount);

	
	ChangeFont("UD デジタル 教科書体 NK-B");	// UD デジタル 教科書体 NK-Bに変更
	ChangeFontType(DX_FONTTYPE_ANTIALIASING);	// アンチエイリアスフォント

	SetFontSize(100);
	DrawFormatString(550, 150,GetColor(255, 255, 255), "ゲーム説明");
	
	SetFontSize(50);
	DrawFormatString(450, 350, GetColor(255, 255, 255),
		"中央に表示される指示に従って");
	DrawFormatString(400, 450, GetColor(255, 255, 255),
		"正しくゲームパットを操作してください");
	
	SetFontSize(20);
	DrawFormatString(710, 850, GetColor(255, 255, 255), "ゲーム画面イメージ");
	
	SetFontSize(30);
	DrawFormatString(1050, 850, GetColor(255, 255, 77),"戻る");

	//	DrawCircle(60, 60, 10, GetColor(255, 255, 255), true);

	// シーン確認用
	//	SetFontSize(50);
	//	DrawFormatString(0, 0, GetColor(255, 255, 255), "タイトル");

		// 今から各画像とすでに描画されているスクリーンとのブレンドの仕方を指定
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeValue);

	// 画面全体を黒に塗りつぶす
	DrawBox(0, 0, 1600, 900, GetColor(0, 0, 0), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}