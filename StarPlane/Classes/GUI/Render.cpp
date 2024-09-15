#define USING_WINAPI
#include <Utils/Config.h>

#include "Render.h"

#include <cassert>
#include <stdexcept>
#include <unordered_map>

#include <resource.h>

#include <GUI/Node.h>

#include <glm/gtc/matrix_transform.hpp>

namespace Game
{
    namespace GUI
    {
        namespace
        {
            Render *render = nullptr;
        }

        Render::Render(unsigned width, unsigned height, const char *title) :
            width_(width), height_(height), title_(title), window_(nullptr)
        {
            Init();
        }

        void Render::Init() noexcept
        {
            if (!glfwInit())
            {
                std::runtime_error error{"Cannot init glfw"};
                exception_ = std::make_exception_ptr(error);
                return;
            }


            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

            window_ = glfwCreateWindow(static_cast<int>(width_), static_cast<int>(height_), title_, nullptr, nullptr);

            if (window_ == nullptr)
            {
                std::runtime_error error{"Cannot create window"};
                exception_ = std::make_exception_ptr(error);
                return;
            }

            glfwMakeContextCurrent(window_);

            const GLenum errorCode = glewInit();
            if (errorCode != GLEW_OK)
            {
                (void)errorCode;
                std::runtime_error error{"Cannot init glew"};
                exception_ = std::make_exception_ptr(error);
                return;
            }

            LoadMatrixProjection();

            glfwSetWindowTitle(window_, title_);

            SetIcon();
        }

        void Render::LoadMatrixProjection() const noexcept
        {
            glViewport(0, 0, static_cast<int>(width_), static_cast<int>(height_));

            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();

            glOrtho(-static_cast<double>(width_), width_, -static_cast<double>(height_), height_, -1, 1);

        }


        void Render::SetIcon() const noexcept
        {
#if defined(_WIN32) && defined(ENABLE_ICON) && ENABLE_ICON
            HMODULE glfw3DLLLib = LoadLibrary(L"glfw3.dll");
            if (!glfw3DLLLib)
            {
                return;
            }

            using Func = HWND (*)(GLFWwindow *);
            Func glfwGetWin32WindowFunc = reinterpret_cast<Func>(GetProcAddress(glfw3DLLLib, "glfwGetWin32Window"));

            if (!glfwGetWin32WindowFunc)
            {
                return;
            }

            HINSTANCE hInstance = GetModuleHandle(nullptr);
            HICON hIcon =
                static_cast<HICON>(LoadImage(hInstance, MAKEINTRESOURCE(APP_ICON), IMAGE_ICON, 32, 32, 0));

            assert(hIcon != nullptr);
            if (hIcon)
            {
                PostMessage(glfwGetWin32WindowFunc(window_), WM_SETICON, ICON_BIG, (LPARAM)hIcon);
            }
            if (hIcon)
            {
                PostMessage(glfwGetWin32WindowFunc(window_), WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
            }
#endif
        }


        void Render::Draw()
        {
            ClearErrors();

            glClear(GL_COLOR_BUFFER_BIT);

            for (size_t i = 0; i < nodes_.size(); ++i)
            {
                auto node = nodes_[i];
                node->Bind();

                glDrawElements(node->RenderMode(), node->IndexCount(), node->IndexElementType(), nullptr);
            }

            glfwSwapBuffers(window_);
            glfwPollEvents();
            PullError();

        }

        void Render::ClearErrors() noexcept
        {
            while (glGetError() != GL_NO_ERROR)
            {

            }
        }

        void Render::PullError() noexcept
        {
            static const std::unordered_map<GLenum, const char *> enumMap = {
                {GL_INVALID_ENUM,
                 "[GL_ERROR]: GL_INVALID_ENUM: An unacceptable value is specified for an enumerated argument. The"
                 "offending command is ignored and has no other side effect than to set the error flag.\n"},
                {GL_INVALID_VALUE,
                 "[GL_ERROR]:GL_INVALID_VALUE: A numeric argument is out of range. The offending command is ignored"
                 "and has no other side effect"
                 "than to set the error flag.\n"},
                {GL_INVALID_OPERATION, "[GL_ERROR]: GL_INVALID_OPERATION:"
                 "The specified operation is not allowed in the current state. The offending command is ignored and"
                 "has no other side effect than to set the error flag.\n"},
                {GL_OUT_OF_MEMORY,
                 "[GL_ERROR]:GL_OUT_OF_MEMORY: There is not enough memory left to execute the command. The state of the GL is undefined,"
                 "except for the state of the error flags, after this error is recorded.\n"},
                {GL_STACK_UNDERFLOW,
                 "[GL_ERROR]:GL_STACK_UNDERFLOW: An attempt has been made to perform an operation that would cause an internal stack to underflow.\n"},
                {GL_STACK_OVERFLOW, "[GL_ERROR]:GL_STACK_OVERFLOW: An attempt has been made to perform an operation that would cause an internal stack to overflow.\n"}
            };
            while (true)
            {
                GLenum error = glGetError();
                if (error == GL_NO_ERROR)
                {
                    return;
                }
#if !defined(NDEBUG)
#if defined(_WIN32)
                OutputDebugStringA(enumMap.at(error));
                __debugbreak();
#else
                std::cerr << enumMap.at(error);
                assert(error == GL_NO_ERROR);
#endif
#endif
                std::runtime_error exception(enumMap.at(error));
                exception_ = std::make_exception_ptr(exception);
                return;
            }
        }


        bool Render::IsRunning() const noexcept
        {
            return !HasException() && !glfwWindowShouldClose(window_);
        }

        bool Render::HasException() const noexcept
        {
            return !window_ || exception_.has_value();
        }


        void Render::Terminate()
        {
            Destroy();
            if (exception_.has_value())
            {
                rethrow_exception(*exception_);
            }

        }

        void Render::InitEventHandler(void (*handler)(GLFWwindow *, int, int, int, int)) const noexcept
        {
            glfwSetKeyCallback(window_, handler);
        }

        void Render::InitOnResizeCallback(void (*handler)(GLFWwindow *, int, int)) const noexcept
        {
            glfwSetFramebufferSizeCallback(window_, handler);
        }

        void Render::OnResize(int width, int height)
        {
            width_ = width;
            height_ = height;
            LoadMatrixProjection();

            for (auto node : nodes_)
            {
                glm::mat4x4 projection =
                    glm::ortho(-GetWidth(), GetWidth(), -GetHeight(), GetHeight());

                node->SetProjection(projection);
            }
        }


        Render::~Render()
        {
            Destroy();
        }


        void Render::Destroy() noexcept
        {
            if (!window_)
            {
                return;
            }
            for (auto node : nodes_)
            {
                ::delete node;
            }
            glfwDestroyWindow(window_);
            window_ = nullptr;
            glfwTerminate();
        }


        void Render::AddNode(Node *node)
        {
            if (!node)
            {
                return;
            }
            nodes_.push_back(node);
        }

        void Render::InitRender(unsigned width, unsigned height, const char *title) noexcept
        {
            if (!render)
            {
                render = ::new Render(width, height, title);
            }
        }


        Render *Render::ResolveRender() noexcept
        {
            return render;
        }


        void Render::ReleaseRender() noexcept
        {
            ::delete render;
        }


        double Render::GetWidth() const noexcept
        {
            return width_;
        }

        double Render::GetHeight() const noexcept
        {
            return height_;
        }


    }
}
