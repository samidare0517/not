#include "PauseScene.h"
#include "InputState.h"
#include "SceneManager.h"
#include <time.h>		// ランダム用
#include "DxLib.h"


PauseScene::PauseScene(SceneManager& manager) : Scene(manager)
{
	// 画像のロード
	catHandle1 = LoadGraph("data/cat/black_1.png");
	catHandle2 = LoadGraph("data/cat/blue_1.png");
	catHandle3 = LoadGraph("data/cat/brown_8.png");

	buttonSTARThandle = LoadGraph("data/button/buttonSTART.png");

	//初期化
	srand((unsigned int)time(NULL));	// 現在時刻の情報で初期化

	// 猫アニメーションのランダム関係の処理
	catNum = rand() % catRandomNum + 1;	// 1～3の乱数を出す
}

PauseScene::~PauseScene()
{
	// 画像のデリート
	DeleteGraph(catHandle1);
	DeleteGraph(catHandle2);
	DeleteGraph(catHandle3);

	DeleteGraph(buttonSTARThandle);
}

void PauseScene::Update(const InputState& input)
{
	if (input.IsTriggred(InputType::pause))
	{
		// ポーズシーンへの移行用のSEの読み込み
		seButtonPause = LoadSoundMem("data/BGM/PauseSE.mp3");

		// SEの音量を調整する
		ChangeVolumeSoundMem(255 * 150 / 100, seButtonPause);

		// SEを呼び出す
		PlaySoundMem(seButtonPause, DX_PLAYTYPE_BACK, false);

		manager_.PopScene();
		return;
	}
}

void PauseScene::Init()
{
	// ランダムで猫を生成する　
	srand((unsigned int)time(NULL));	// 現在時刻の情報で初期化
	catNum = rand() % catRandomNum + 1;		// 1～3の乱数を出す
}

void PauseScene::CatAnimationDraw()
{
	

	switch (catNum)
	{
	case 1:
		DrawRectRotaGraph(1000, 670,			//表示したい座標の指定
			32 * animationNumber, 32 + (32 * imgidx),			//切り取り左上    （+32は上のよくわかんないやつを省いてる）
			32, 32,							//幅、高さ（画像の大きさ32）
			2.5f, 0.0f,						//拡大率、回転角度
			catHandle1, true);
		break;
	case 2:
		DrawRectRotaGraph(1000, 670,			//表示したい座標の指定
			32 * animationNumber, 32 + (32 * imgidx),			//切り取り左上    （+32は上のよくわかんないやつを省いてる）
			32, 32,							//幅、高さ（画像の大きさ32）
			2.5f, 0.0f,						//拡大率、回転角度
			catHandle2, true);
		break;
	case 3:
		DrawRectRotaGraph(1000, 670,			//表示したい座標の指定
			32 * animationNumber, 32 + (32 * imgidx),			//切り取り左上    （+32は上のよくわかんないやつを省いてる）
			32, 32,							//幅、高さ（画像の大きさ32）
			2.5f, 0.0f,						//拡大率、回転角度
			catHandle3, true);
		break;
	}

	//アニメーションが最後まで行ったらゼロに戻してあげる
	if (animationNumber > 14)
	{
		animationNumber = 0;
	}

	timer++;        //時間のカウント
	if (timer >= 15)
	{
		//インターバルより大きくなったらアニメーションを動かす
		animationNumber++;
		timer = 0;
	}
}

void PauseScene::Draw()
{
	constexpr int pw_width  = 500;	// ポーズ枠の幅
	constexpr int pw_height = 500;	// ポーズ枠の高さ
	constexpr int pw_start_x = (1600 - pw_width) / 2;	// ポーズ枠左
	constexpr int pw_start_y = (900 - pw_height) / 2;	// ポーズ枠上

//	SetDrawBlendMode(DX_BLENDMODE_MULA, 128);	// 乗算合成
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	// 画面を暗くする
	DrawBox(0, 0, 1600, 900, GetColor(0, 0, 0), TRUE);

	// 通常描画に戻す
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	// 青のポーズウインドウ
	DrawBox(pw_start_x, pw_start_y,
			pw_start_x + pw_width,
			pw_start_y + pw_height,
			GetColor(71, 83 ,162), true);

	// ポーズウィンドウ枠線
	DrawBox(pw_start_x, pw_start_y,
			pw_start_x + pw_width,
			pw_start_y + pw_height,
			0xffffff, false);

	// ポーズ中メッセージ
	SetFontSize(80);
	DrawString(pw_start_x + 20, pw_start_y + 210, "Pauseing...", GetColor(255, 255, 127));

	// 戻り案内
	DrawGraph(630, 645, buttonSTARThandle, true);
	SetFontSize(20);
	DrawFormatString(560, 670, GetColor(255, 255, 255), "戻る ・・・");

	CatAnimationDraw();

}
