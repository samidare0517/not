#include "DxLib.h"
#include <cassert>
#include<array>
#include "SceneManager.h"
#include "TitleScene.h"
#include "InputState.h"
#include "TimeBar.h"
#include "KeyField.h"
#include "math.h"
#include "game.h"

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // windowモード設定
    ChangeWindowMode(Game::kWindowMode);

    // ウインドウ名設定
    SetMainWindowText("Simple Brain Training");

    // 画面サイズの設定
    SetGraphMode(Game::kScreenWindth, Game::kScreenHeight, Game::kColorDepth);

    if (DxLib_Init() == -1)        // ＤＸライブラリ初期化処理
    {
        return -1;            // エラーが起きたら直ちに終了
    }

    // ダブルバッファモード
    SetDrawScreen(DX_SCREEN_BACK);

  

    InputState input;
    SceneManager sceneManager;
    sceneManager.CangeScene(new TitleScene(sceneManager));

   
    while (ProcessMessage() == 0)
    {
        LONGLONG time = GetNowHiPerformanceCount();

        // 画面のクリア
        ClearDrawScreen();

        input.Update();
        sceneManager.Update(input);
        sceneManager.Draw();


      
        // 裏画面を表画面を入れ替える
        ScreenFlip();
  
        // escキーを押したら終了する
        if (CheckHitKey(KEY_INPUT_ESCAPE))
        {
            break;
        }

        // fpsを60に固定
        while (GetNowHiPerformanceCount() - time < 16667)
        {

        }

    }

    sceneManager.End();     // 先に全てのdelete処理をここでする

    DxLib_End();                // ＤＸライブラリ使用の終了処理

    return 0;                // ソフトの終了
}