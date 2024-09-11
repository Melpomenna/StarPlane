#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include "Render.h"

#include <cassert>
#include <GL/gl.h>
#include <stdexcept>

#include <resource.h>

namespace Game
{
    namespace GUI
    {
        Render::Render(unsigned width, unsigned height, const char *title) :
            width_(width), height_(height), title_(title), window_(nullptr), exception_(nullptr)
        {
            Init();
        }

        void Render::Init() noexcept
        {
            if (glfwInit() != GLFW_TRUE)
            {
                std::runtime_error error{"Cannot init glfw"};
                *exception_ = std::make_exception_ptr(error);
                return;
            }

            window_ = glfwCreateWindow(width_, height_, title_, nullptr, nullptr);

            if (window_ == nullptr)
            {
                std::runtime_error error{"Cannot create window"};
                *exception_ = std::make_exception_ptr(error);
                return;
            }

            glfwMakeContextCurrent(window_);

            glfwSetWindowTitle(window_, title_);
            SetIcon();
        }

        void Render::SetIcon() const noexcept
        {
            auto glfw3DLLLib = LoadLibrary(L"glfw3.dll");
            if (!glfw3DLLLib)
                return;

            using Func = HWND (*)(GLFWwindow *);
            auto glfwGetWin32WindowFunc = reinterpret_cast<Func>(GetProcAddress(glfw3DLLLib, "glfwGetWin32Window"));

            if (!glfwGetWin32WindowFunc)
                return;

            auto hInstance = GetModuleHandle(nullptr);
            auto hIcon =
                static_cast<HICON *>(LoadImage(hInstance, MAKEINTRESOURCE(APP_ICON), IMAGE_ICON, 32, 32, 0));

            assert(hIcon != nullptr);
            if (hIcon)
            {
                SendMessage(glfwGetWin32WindowFunc(window_), WM_SETICON, ICON_BIG, (LPARAM)hIcon);
            }
            if (hIcon)
            {
                SendMessage(glfwGetWin32WindowFunc(window_), WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
            }
        }


        void Render::Draw()
        {
            glClearColor(0, 0, 0, 1);

            glfwSwapBuffers(window_);
            glfwPollEvents();
        }

        bool Render::IsRunning() const noexcept
        {
            return window_ && !HasException() && !glfwWindowShouldClose(window_);
        }

        bool Render::HasException() const noexcept
        {
            return exception_ != nullptr;
        }


        void Render::Terminate()
        {
            Destroy();
            if (exception_ != nullptr)
            {
                rethrow_exception(*exception_);
            }

        }


        Render::~Render()
        {
            Destroy();
        }


        void Render::Destroy() noexcept
        {
            glfwDestroyWindow(window_);
            window_ = nullptr;
            glfwTerminate();
        }


    }
}
