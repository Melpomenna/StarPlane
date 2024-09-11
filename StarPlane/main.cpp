#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <Utils/Config.h>
#include <Application.h>

int APIENTRY WinMain(IN HINSTANCE hInstance, IN HINSTANCE hPrevInstance, IN LPSTR lpCmdLine, IN int nShowCommand)
{

    auto app = std::make_unique<Game::Application>(APP_WIDTH,APP_HEIGHT,APP_TITLE);

    return app->Run();
}
