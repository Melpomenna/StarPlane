#pragma once

#include <exception>

#include <GL/glew.h>
#define GLFW_DLL
#include <GLFW/glfw3.h>

#include <Utils/Optional.h>
#include <vector>

namespace Game
{

    namespace GUI
    {

        class Node;

        class Render final
        {
        public:
            friend class Application;

            Render() = delete;
            explicit Render(unsigned, unsigned, const char *);
            ~Render();

            Render(const Render &) = delete;
            Render &operator=(const Render &) = delete;

            bool IsRunning() const noexcept;
            void Draw();
            bool HasException() const noexcept;
            void Terminate();

            void AddNode(Node *);

            static Render *ResolveRender() noexcept;

            double GetWidth() const noexcept;
            double GetHeight() const noexcept;

            void OnResize(int, int);

        private:
            using KeyboardCallbackType = void (*)(GLFWwindow *, int, int, int, int);
            using MouseKeyboardCallbackType = void (*)(GLFWwindow *, int, int, int);
            using ResizeWindowCallbackType = void (*)(GLFWwindow *, int, int);

            void InitKeyboardEventHandler(KeyboardCallbackType) const noexcept;
            void InitMouseEventHandler(MouseKeyboardCallbackType) const noexcept;
            void InitOnResizeCallback(ResizeWindowCallbackType) const noexcept;

            static void ReleaseRender() noexcept;
            static void InitRender(unsigned, unsigned, const char *) noexcept;

            void LoadMatrixProjection() const noexcept;

            void Init() noexcept;
            void Destroy() noexcept;

            void SetIcon() const noexcept;
            static void ClearErrors() noexcept;
            void PullError() noexcept;

        private:
            unsigned width_, height_;
            const char *title_;
            GLFWwindow *window_;
            Optional<std::exception_ptr> exception_;
            std::vector<Node *> nodes_;
        };
    } // namespace GUI

} // namespace Game
