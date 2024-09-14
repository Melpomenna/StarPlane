#include "Application.h"

#include <Utils/Config.h>

#include <GUI/Render.h>
#include <Utils/Timer.h>
#include <Utils/Cache.h>
#include <GUI/Node.h>

#include <glm/gtc/matrix_transform.hpp>

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

            double vertexBuffer[] = {
                -static_cast<double>(width_) / 2.0, 0.0,
                width_ / 2.0, 0.0,
                0, height_ / 2.0
            };

            unsigned int index[] = {
                0, 1, 2
            };

            GUI::Node *triangle = ::new GUI::Node(
                SHADERS_PATH(BasicVertex.vert), SHADERS_PATH(BasicFrag.frag), GL_STATIC_DRAW);
            triangle->StoreBuffers(vertexBuffer, std::size(vertexBuffer), index, std::size(index));
            triangle->FillColor(0.5, 1, 0);
            glm::mat4x4 model = glm::mat4(1.0f);
            glm::mat4x4 projection = glm::ortho(-static_cast<float>(width_), static_cast<float>(width_),
                                                -static_cast<float>(height_), static_cast<float>(height_));
            triangle->SetModel(model);
            triangle->SetProjection(projection);
            double dt = 1E-6;
            render_->AddNode(triangle);


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
