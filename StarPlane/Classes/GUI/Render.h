#pragma once

#include <exception>

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
            Render() = delete;
            explicit Render(unsigned width, unsigned height, const char *title);
            ~Render();

            Render(const Render &) = delete;
            Render &operator=(const Render &) = delete;

            bool IsRunning() const noexcept;
            void Draw();
            bool HasException() const noexcept;
            void Terminate();

            void AddNode(Node*);

        private:
            void Init() noexcept;
            void Destroy() noexcept;

            void SetIcon() const noexcept;
            static void ClearErrors() noexcept;
            void PullError() noexcept;

        private:
            const unsigned width_, height_;
            const char *title_;
            GLFWwindow *window_;
            Optional<std::exception_ptr> exception_;
            std::vector<Node *> nodes_;
        };
    } // namespace GUI

} // namespace Game
