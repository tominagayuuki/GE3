#include"Input.h"
#include"WinApp.h"
#include"DirectXCommon.h"


// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

#pragma region 基盤システムの初期化
    WinApp* winApp = nullptr;
    //WindowsAPIの初期化
    winApp = new WinApp();
    winApp->initialize();

    DirectXCommon* dxCommon = nullptr;
    //DirectXの初期化
    dxCommon = new DirectXCommon();
    dxCommon->Initialize(winApp);

    //ポインタ
    Input* input = nullptr;
    //入力の初期化
    input = new Input();
    input->Initialize(winApp);
   
    HRESULT result;
    //MSG msg{};  // メッセージ
#pragma endregion

#pragma region 最初のシーンの初期化


#pragma endregion

    //ゲームループ
    while (true) {

#pragma region 基盤システム更新
        if (winApp->ProcessMessage() == true) {
            break;
        }
        //入力処理
        input->Update();

#pragma endregion

#pragma region 最初のシーン更新

#pragma endregion

        //描画前処理
        dxCommon->PreDraw();

#pragma region 最初のシーン描画

#pragma endregion
        //描画後処理
        dxCommon->PostDraw();
    }

#pragma region 最初のシーン終了

#pragma endregion

#pragma region 基盤システム終了
    // ウィンドウクラスを登録解除
    delete input;
    input = nullptr;

    delete dxCommon;
    dxCommon = nullptr;

    winApp->Finalize();
    delete winApp;
    winApp = nullptr;
#pragma endregion

    return 0;
}
