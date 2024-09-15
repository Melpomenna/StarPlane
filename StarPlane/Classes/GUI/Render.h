#pragma once

#include <exception>

#include <GL/glew.h>
#define GLFW_DLL
#include <GLFW/glfw3.h>

#include <Utils/Optional.h>
#include <vector>

namespace Game
{
    class Application;

    namespace GUI
    {

        class Node;

        class Render final
        {
        public:
            friend class Application;

            Render() = delete;
            explicit Render(unsigned width, unsigned height, const char *title);
            ~Render();

            Render(const Render &) = delete;
            Render &operator=(const Render &) = delete;

            bool IsRunning() const noexcept;
            void Draw();
            bool HasException() const noexcept;
            void Terminate();

            void AddNode(Node *);

            static Render *ResolveRender() noexcept;

        private:
            static void ReleaseRender() noexcept;
            static void InitRender(unsigned width, unsigned height, const char *title) noexcept;

            void Init() noexcept;
            void Destroy() noexcept;

            void SetIcon() const noexcept;
            static void ClearErrors() noexcept;
            void PullError() noexcept;
            void LoadMatrixProjection() const noexcept;

        private:
            const unsigned width_, height_;
            const char *title_;
            GLFWwindow *window_;
            Optional<std::exception_ptr> exception_;
            std::vector<Node *> nodes_;
        };
    } // namespace GUI

} // namespace Game
