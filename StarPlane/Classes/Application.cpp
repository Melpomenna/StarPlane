#include "Application.h"

#include <string>
#include <Utils/Config.h>

#include <Core/Controller/EventControllerProcessor.h>
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
        timer_ = std::make_shared<Timer>();
    }

    int Application::Run() const noexcept
    {
        int statusCode{};
        try
        {

            auto actorSystem = Core::ActorSystem::ResolveActorSystem();
            const auto render = GUI::Render::ResolveRender();

            AppDelegate *delegate = ::new AppDelegate();

            while (render->IsRunning())
            {
                double dt = 1E-6;
                timer_->Mark();
                render->Draw();
                actorSystem->Update(dt);
                dt = timer_->Peek();
                render->RemoveUnusedNodes();
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
