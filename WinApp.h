#pragma once
#include <Windows.h>

class WinApp
{
public:
	static LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
public:
	void initialize();

	void Update();

	void Finalize();

	HWND GetHwnd() const { return hwnd; }

	HINSTANCE GetHInstance() const { return w.hInstance; }

	bool ProcessMessage();

public://�萔
	//�E�B���h�E����
	static const int window_width = 1280;
	//�E�B���h�E�c��
	static const int window_height = 720;
private:
	HWND hwnd = nullptr;

	WNDCLASSEX w{};
};

