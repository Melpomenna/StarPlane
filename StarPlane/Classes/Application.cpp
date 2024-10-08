#include "Application.h"

#include <string>
#include <Utils/Config.h>

#include <Core/Controller/EventControllerProcessor.h>
#include <Core/Controller/Mouse/IMouseProcessor.h>
#include <Core/Actor/ActorSystem.h>
#include <GUI/Render.h>
#include <Utils/Cache.h>
#include <Utils/Timer.h>

#include <Game/AppDelegate.h>

namespace Game
{
    namespace
    {
        void KeyboardEventControl(GLFWwindow *, const int key, const int scancode, const int action,
                                  const int modes) noexcept
        {
#if defined(ENABLE_LOG)
            std::string data = "Keyboard: key:" + std::to_string(key) + " scancode:" + std::to_string(scancode) +
                " action:" + std::to_string(action) + " modes:" + std::to_string(modes) + "\n";
            APP_LOG(data.c_str());
#endif

            Core::EventControllerProcessor::ResolveEventController()->PushEvent(key, action, modes);
        }

        void MouseEventControl(GLFWwindow *, const int key, const int action, const int modes) noexcept
        {
#if defined(ENABLE_LOG)
            std::string data = "Mouses: key:" + std::to_string(key) +
                " action:" + std::to_string(action) + " modes:" + std::to_string(modes) + "\n";
            APP_LOG(data.c_str());
#endif

            Core::EventControllerProcessor::ResolveEventController()->PushEvent(key, action, modes);
        }

        void OnResize(GLFWwindow *, const int width, const int height)
        {
#if defined(ENABLE_LOG)
            APP_LOG(("Resize window: (w,h)" + std::to_string(width) + "," + std::to_string(height) + "\n").c_str());
#endif
            GUI::Render::ResolveRender()->OnResize(width, height);
            Core::ActorSystem::ResolveActorSystem()->OnResize(width, height);
        }

        void OnCursorMove(GLFWwindow *, const double x, const double y)
        {
#if defined(ENABLE_LOG)
            APP_LOG(("OnMove cursor: (x,y)" + std::to_string(x) + "," + std::to_string(y) + "\n").c_str());
#endif
            Core::EventControllerProcessor::ResolveEventController()->Mouse()->OnMove(x, y);
        }

    } // namespace

    Application::Application(const unsigned width, const unsigned height, const char *title) :
        width_(width), height_(height), title_(title)
    {
        Init();
    }

    void Application::Init() noexcept
    {
        Core::ActorSystem::Init();
        GUI::Render::InitRender(width_, height_, title_);
        Core::EventControllerProcessor::Init();
        GUI::Render::ResolveRender()->InitKeyboardEventHandler(KeyboardEventControl);
        GUI::Render::ResolveRender()->InitMouseEventHandler(MouseEventControl);
        GUI::Render::ResolveRender()->InitOnResizeCallback(OnResize);
        GUI::Render::ResolveRender()->InitMouseMoveEventHandler(OnCursorMove);
        timer_ = std::make_shared<Timer>();
    }

    int Application::Run() const noexcept
    {
        int statusCode{};
        try
        {

            auto actorSystem = Core::ActorSystem::ResolveActorSystem();
            const auto render = GUI::Render::ResolveRender();
            auto eventController = Core::EventControllerProcessor::ResolveEventController();

            AppDelegate *delegate = new AppDelegate();

            double dt = 1E-6;
            while (render->IsRunning())
            {
                timer_->Mark();
                render->Draw();
                // No unused, because keyboardProcess and MouseProcessor in Update method do nothing
                eventController->Update(dt);
                actorSystem->Update(dt);
                actorSystem->CollisionDetection();
                actorSystem->RemoveDestroyedActors();
                render->RemoveUnusedNodes();
                dt = timer_->Peek();
#if defined(ENABLE_LOG)
                std::string deltaTimeMessage = "Delta Time:" + std::to_string(dt) + "\n";
                APP_LOG(deltaTimeMessage.c_str());
#endif

            }
            if (render->HasException())
            {
                render->Terminate();
            }

        }
        catch (...)
        {
            statusCode = -1;
        }
        return statusCode;
    }

    Application::~Application()
    {
        Destroy();
    }

    void Application::Destroy() noexcept
    {
        Cache::Release();
        Core::ActorSystem::Destroy();
        Core::EventControllerProcessor::ResolveEventController();
        GUI::Render::ReleaseRender();
    }


} // namespace Game
