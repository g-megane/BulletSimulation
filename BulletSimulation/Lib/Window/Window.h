#pragma once
#ifndef WINDOW_H
#define WINDOW_H
#ifndef STRICT
#define STRICT
#endif
#define WIN32_LEAN_AND_MEAN
/*
STRICT
    �E�����Ȍ^�`�F�b�N�������Ȃ���悤�ɂȂ�
WIN32_LEAN_AND_MEAN
    �E�K�v�Œ���̃w�b�_�̂݃C���N���[�h
    �E�R���p�C�����Ԃ̒Z�k
*/

#include <Windows.h>

namespace Lib
{
    class Window
    {
    public:
        Window(const LPCWSTR _windowName, const LONG _windowWidth, const LONG _windowHeight);
        ~Window();

        MSG Update();
        HWND getHWND() const;
        RECT getWindowRect() const;
        bool getKeyDown(BYTE key);

    private:
        HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow);
        static LRESULT CALLBACK WndProck(HWND _hWnd, UINT message, WPARAM wParam, LPARAM lParam);
        int Initialize();

        LPCWSTR windowName;
        HWND hWnd;
        RECT windowRect;
        BYTE keyTbl[256];
    };
}
#endif