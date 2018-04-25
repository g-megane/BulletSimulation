#include "Window.h"

namespace Lib
{
    // �R���X�g���N�^
    Window::Window(const LPCWSTR _windowName, const LONG _windowWidth, const LONG _windowHeight)
        :windowName(_windowName)
    {
        windowRect = { 0, 0, _windowWidth, _windowHeight };
        Initialize();
    }

    // �f�X�g���N�^
    Window::~Window()
    {
    }

    // ������
    int Window::Initialize()
    {
        auto hInstance = GetModuleHandle(nullptr);
        auto nCmdShow  = SW_SHOWNORMAL;

        if (FAILED(InitWindow(hInstance, nCmdShow))) {
            OutputDebugString(L"InitWindow()�̎��s");
            return 0;
        }

        return 0;
    }
    
    // hWnd�̎擾
    HWND Window::getHWND() const
    {
        return hWnd;
    }

    RECT Window::getWindowRect() const
    {
        return windowRect;
    }

    bool Window::getKeyDown(BYTE key)
    {
        return keyTbl[key] & 0x80;
    }
    
    // �E�B���h�E�̏�����
    HRESULT Window::InitWindow(HINSTANCE hInstance, int nCmdShow)
    {
        WNDCLASSEX wcex;
        wcex.cbSize        = sizeof(WNDCLASSEX);						 // �\���̂̃T�C�Y
        wcex.style         = CS_HREDRAW | CS_VREDRAW;					 // �E�B���h�E�X�^�C��
        wcex.lpfnWndProc   = WndProck;							         // �E�B���h�E�v���V�[�W��
        wcex.cbClsExtra    = 0;									         // �E�B���h�E�N���X�ɕt��������������
        wcex.cbWndExtra    = 0;									         // �E�B���h�E�ɕt��������������
        wcex.hInstance     = hInstance;								     // �C���X�^���X�n���h��
        wcex.hIcon         = nullptr;									 // �A�C�R��
        wcex.hCursor       = nullptr;									 // �J�[�\��
        wcex.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1); // �w�i�F
        wcex.lpszMenuName  = windowName;								 // ���j���[
        wcex.lpszClassName = windowName;								 // �E�B���h�E�N���X�̖��O
        wcex.hIconSm       = nullptr;									 // �A�C�R����
        if (!RegisterClassEx(&wcex)) {
            OutputDebugString(L"RegisterClassEx()�̎��s");
            return E_FAIL;
        }

        // �E�B���h�E�̍쐬
        AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, FALSE);
        hWnd = CreateWindow(
            windowName,				// �E�B���h�E�N���X��
            windowName,				// �E�B���h�E�^�C�g��
            WS_OVERLAPPEDWINDOW,    // ^ WS_MAXIMIZEBOX ^ WS_THICKFRAME | WS_VISIBLE,	// �E�B���h�E�X�^�C��
            CW_USEDEFAULT,			// Y���W�̏����l
            CW_USEDEFAULT,			// X���W�̏����l
            windowRect.right  - windowRect.left, // ���̏����l
            windowRect.bottom - windowRect.top, // �����̏����l
            nullptr,				// �e�E�B���h�E�̃n���h��
            nullptr,				// �E�B���h�E���j���[
            hInstance,				// �C���X�^���X�n���h��
            nullptr);				// �쐬�p�����[�^
        if (!hWnd) {
            OutputDebugString(L"CreateWindow()�̎��s");
            return E_FAIL;
        }

        // ����{�^���̖�����
        // EnableMenuItem(GetSystemMenu(hWnd, NULL), SC_CLOSE, MF_DISABLED);

        ShowWindow(hWnd, nCmdShow);

        return S_OK;
    }
    // �E�B���h�E�v���V�[�W��
    LRESULT Window::WndProck(HWND _hWnd, UINT message, WPARAM wParam, LPARAM lParam)
    {
        PAINTSTRUCT ps;
        HDC hdc;

        switch (message)
        {
        case WM_PAINT:
            hdc = BeginPaint(_hWnd, &ps);
            EndPaint(_hWnd, &ps);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        case WM_KEYDOWN:
            // Esc�ŏI��
            if (wParam == VK_ESCAPE) {
                PostQuitMessage(0);
            }
            break;
        default:
            return DefWindowProc(_hWnd, message, wParam, lParam);
        }

        return 0;
    }
    // �A�b�v�f�[�g
    MSG Window::Update()
    {
        MSG msg = { 0 };
        if (!GetKeyboardState(keyTbl)) {
            MessageBox(hWnd, L"�L�[���̎擾�Ɏ��s", L"ERROR", MB_OK);
        }

        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        return msg;
    }
}