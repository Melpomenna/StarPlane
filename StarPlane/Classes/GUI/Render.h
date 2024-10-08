#pragma once

#include <exception>

#include <GL/glew.h>
#define GLFW_DLL
#include <GLFW/glfw3.h>

#include <Utils/Optional.h>
#include <deque>

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
            void RemoveNode(Node *);
            void MoveToBack(Node *);

			void SetTitle(std::string&&);

            Node *GetNodeByName(std::string &&) const noexcept;

            template <class T>
            T *GetNodeByNameAs(std::string &&name) const noexcept
            {
                static_assert(std::is_base_of_v<Node, T>);

                return static_cast<T *>(GetNodeByName(std::move(name)));
            }

            static Render *ResolveRender() noexcept;

            double GetWidth() const noexcept;
            double GetHeight() const noexcept;

            void OnResize(int, int);

            void RemoveUnusedNodes();

            std::pair<double, double> GetCursorPosition() const noexcept;

        private:
            using KeyboardCallbackType = void (*)(GLFWwindow *, int, int, int, int);
            using MouseCallbackType = void (*)(GLFWwindow *, int, int, int);
            using ResizeWindowCallbackType = void (*)(GLFWwindow *, int, int);
            using MouseMoveCallbackType = void(*)(GLFWwindow *, double, double);

            void InitKeyboardEventHandler(KeyboardCallbackType) const noexcept;
            void InitMouseEventHandler(MouseCallbackType) const noexcept;
            void InitOnResizeCallback(ResizeWindowCallbackType) const noexcept;
            void InitMouseMoveEventHandler(MouseMoveCallbackType) const noexcept;

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
            std::string title_;
            GLFWwindow *window_;
            Optional<std::exception_ptr> exception_;
            std::deque<Node *> nodes_;
        };
    } // namespace GUI

} // namespace Game
