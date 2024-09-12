#include "Application.h"

#include <GUI/Render.h>
#include <Utils/Timer.h>
#include <Utils/Cache.h>

namespace Game
{
    Application::Application(unsigned width, unsigned height, const char *title) :
        width_(width), height_(height), title_(title)
    {
        Init();
    }

    void Application::Init() noexcept
    {
        render_ = std::make_unique<GUI::Render>(width_, height_, title_);
        timer_ = std::make_shared<Timer>();
    }

    int Application::Run() noexcept
    {
        int statusCode{};
        try
        {
            double dt = 1E-6;
            while (render_->IsRunning())
            {
                timer_->Mark();
                render_->Draw();
                dt = timer_->Peek();
            }
            if (render_->HasException())
            {
                render_->Terminate();
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
    }


}
