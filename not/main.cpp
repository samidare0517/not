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

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // window���[�h�ݒ�
    ChangeWindowMode(Game::kWindowMode);

    // �E�C���h�E���ݒ�
    SetMainWindowText("Simple Brain Training");

    // ��ʃT�C�Y�̐ݒ�
    SetGraphMode(Game::kScreenWindth, Game::kScreenHeight, Game::kColorDepth);

    if (DxLib_Init() == -1)        // �c�w���C�u��������������
    {
        return -1;            // �G���[���N�����璼���ɏI��
    }

    // �_�u���o�b�t�@���[�h
    SetDrawScreen(DX_SCREEN_BACK);

  

    InputState input;
    SceneManager sceneManager;
    sceneManager.CangeScene(new TitleScene(sceneManager));

   
    while (ProcessMessage() == 0)
    {
        LONGLONG time = GetNowHiPerformanceCount();

        // ��ʂ̃N���A
        ClearDrawScreen();

        input.Update();
        sceneManager.Update(input);
        sceneManager.Draw();


      
        // ����ʂ�\��ʂ����ւ���
        ScreenFlip();
  
        // esc�L�[����������I������
        if (CheckHitKey(KEY_INPUT_ESCAPE))
        {
            break;
        }

        // fps��60�ɌŒ�
        while (GetNowHiPerformanceCount() - time < 16667)
        {

        }

    }

    sceneManager.End();     // ��ɑS�Ă�delete�����������ł���

    DxLib_End();                // �c�w���C�u�����g�p�̏I������

    return 0;                // �\�t�g�̏I��
}