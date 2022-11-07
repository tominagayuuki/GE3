#pragma once
#include <windows.h>
#include <wrl.h>
#define DIRECTINPUT_VERSION     0x0800   // DirectInputのバージョン指定
#include <dinput.h>
#include"WinApp.h"


class Input
{
public:
	// namespace省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public: // メンバ関数
	void Initialize(WinApp* winApp);
	void Update();

	bool PushKey(BYTE keyNumber);

	bool TriggerKey(BYTE keyNumber);

private: // メンバ変数
	//DirectInputのインスタンス
	ComPtr<IDirectInput8> directInput;
// キーボードのデバイス
	ComPtr<IDirectInputDevice8> keyboard;
	BYTE key[256] = {};
	//
	BYTE keyPre[256] = {};

	WinApp* winApp = nullptr;
};
