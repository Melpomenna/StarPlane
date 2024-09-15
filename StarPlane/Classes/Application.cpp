#include "Application.h"

#include <Utils/Config.h>

#include <GUI/Node.h>
#include <GUI/Support.h>
#include <GUI/Render.h>
#include <Utils/Cache.h>
#include <Utils/Timer.h>

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


            constexpr double width = 150;
            constexpr double height = 150;
            GUI::Node *player = GUI::CreateRectangle(width, height);
            player->LoadTexture(TEXTURE_PATH(Plane.png));
            double dt = 1E-6;
            render_->AddNode(player);

            player->SetPos(-static_cast<double>(width_) / 3, 0);


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


} // namespace Game
