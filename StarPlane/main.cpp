#if defined(_WIN32)
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif

#include <Utils/Config.h>
#include <Application.h>

#if defined(_WIN32)
int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine,
                     _In_ int nShowCommand)
#else
int main(int argc, char** argv)
#endif
{

    std::unique_ptr<Game::Application> app = std::make_unique<Game::Application>(APP_WIDTH, APP_HEIGHT, APP_TITLE);

    return app->Run();
}
