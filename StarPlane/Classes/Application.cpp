#include "Application.h"

#include <GUI/Render.h>

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
    }

    int Application::Run() noexcept
    {
        int statusCode{};
        try
        {
            while (render_->IsRunning())
            {
                render_->Draw();
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

    }


}
