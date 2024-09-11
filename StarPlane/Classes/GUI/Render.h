#pragma once

#include <exception>

#include <GLFW/glfw3.h>

namespace Game
{

    namespace GUI
    {

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

        private:
            void Init() noexcept;
            void Destroy() noexcept;

			void SetIcon() const noexcept;
        private:
            const unsigned width_, height_;
            const char *title_;
            GLFWwindow *window_;
            std::exception_ptr *exception_;
        };
    } // namespace GUI

} // namespace Game
