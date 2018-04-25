#include <memory>
#include <sstream>
#include <locale>
#include "Lib\Window\Window.h"
#include "Lib\Common\Time.h"

using namespace Lib;

const float FPS = 60.0f;

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
    UNREFERENCED_PARAMETER(hInstance);
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    UNREFERENCED_PARAMETER(nCmdShow);

    // Windowクラスの作成
    auto window = std::make_shared<Window>(L"BulletSimulation", 1026, 768);
    // Timeクラスの作成
    auto time = Time();
    int fpsCount = 0;
    float countTime = 0.0f;
    float deltaTime = 0.0f;
    std::ostringstream oss;
    WCHAR wcstr[50];
    size_t size = 0;
    setlocale(LC_ALL, "japanese"); // 後のmbstowcs_sの為の処理

    while (window->Update().message != WM_QUIT) {
        
        if (!time.timeOver(1000.0f / FPS)) {
            continue;
        }

        deltaTime = time.getDeltaTime();
        countTime += deltaTime;

        // 1秒に1回行う処理
        if (countTime > 1000.0f) {
            // FPSをデバッガに出力
            oss.str("");
            oss << "FPS: " << fpsCount << std::endl;
            mbstowcs_s(&size, wcstr, 20, oss.str().c_str(), _TRUNCATE);
            OutputDebugString(wcstr);
            // 変数のリセット
            fpsCount = 0;
            countTime = 0.0f;
        }

        time.reset();
        ++fpsCount;
    }

    return 0;
}