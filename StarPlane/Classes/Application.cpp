#include "Application.h"

#include <string>
#include <Utils/Config.h>

#include <GUI/Node.h>
#include <GUI/Support.h>
#include <GUI/Render.h>
#include <Utils/Cache.h>
#include <Utils/Timer.h>

namespace Game
{
    void EventControl(GLFWwindow *, int key, int scancode, int action, int modes)
    {
        std::string data = "key:" + std::to_string(key) + " scancode:" + std::to_string(scancode) +
            " action:" + std::to_string(action) + " modes:" + std::to_string(modes) + "\n";
        APP_LOG(data.c_str());
    }

    void OnResize(GLFWwindow *window, int width, int height)
    {
        (void)window;
        GUI::Render::ResolveRender()->OnResize(width, height);
    }

    Application::Application(unsigned width, unsigned height, const char *title) :
        width_(width), height_(height), title_(title)
    {
        Init();
    }

    void Application::Init() noexcept
    {
        GUI::Render::InitRender(width_, height_, title_);
        GUI::Render::ResolveRender()->InitEventHandler(EventControl);
        GUI::Render::ResolveRender()->InitOnResizeCallback(OnResize);
        timer_ = std::make_shared<Timer>();
    }

    int Application::Run() noexcept
    {
        int statusCode{};
        try
        {


            constexpr double width = 150;
            constexpr double height = 150;
            GUI::Node *player = GUI::CreateRectangle(width, height);
            player->LoadTexture(TEXTURE_PATH(Plane.png));
            double dt = 1E-6;
            auto render = GUI::Render::ResolveRender();
            render->AddNode(player);

            player->SetPos(-static_cast<double>(width_) / 3, 0);


            while (render->IsRunning())
            {
                timer_->Mark();
                render->Draw();
                dt = timer_->Peek();
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
        GUI::Render::ReleaseRender();
    }


} // namespace Game
