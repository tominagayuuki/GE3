#pragma once
#include <windows.h>
#include <wrl.h>
#define DIRECTINPUT_VERSION     0x0800   // DirectInput�̃o�[�W�����w��
#include <dinput.h>
#include"WinApp.h"


class Input
{
public:
	// namespace�ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public: // �����o�֐�
	void Initialize(WinApp* winApp);
	void Update();

	bool PushKey(BYTE keyNumber);

	bool TriggerKey(BYTE keyNumber);

private: // �����o�ϐ�
	//DirectInput�̃C���X�^���X
	ComPtr<IDirectInput8> directInput;
// �L�[�{�[�h�̃f�o�C�X
	ComPtr<IDirectInputDevice8> keyboard;
	BYTE key[256] = {};
	//
	BYTE keyPre[256] = {};

	WinApp* winApp = nullptr;
};
