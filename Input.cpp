#include "input.h"
#include <cassert>


#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")



void Input::Initialize(WinApp* winApp) {
    this->winApp = winApp;

    HRESULT result;

    // DirectInput�̏�����
   
    result = DirectInput8Create(
        winApp->GetHInstance(), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&directInput, nullptr);
    assert(SUCCEEDED(result));

    // �L�[�{�[�h�f�o�C�X�̐���
    result = directInput->CreateDevice(GUID_SysKeyboard, &keyboard, NULL);
    // ���̓f�[�^�`���̃Z�b�g
    result = keyboard->SetDataFormat(&c_dfDIKeyboard); // �W���`��
    assert(SUCCEEDED(result));
    // �r�����䃌�x���̃Z�b�g
    result = keyboard->SetCooperativeLevel(
        winApp->GetHwnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
    assert(SUCCEEDED(result));

}

void Input::Update() {

    memcpy(keyPre, key, sizeof(key));

    // �L�[�{�[�h���̎擾�J�n
    keyboard->Acquire();
    // �S�L�[�̓��͏�Ԃ��擾����
    keyboard->GetDeviceState(sizeof(key), key);


}

bool Input::PushKey(BYTE keyNumber)
{
    if (key[keyNumber]) {
        return true;
    }
    return false;
}

bool Input::TriggerKey(BYTE keyNumber)
{
    if (key[keyNumber] && !keyPre[keyNumber]) {
        return true;
    }
    return false;
}
