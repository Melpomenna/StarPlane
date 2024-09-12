#pragma once

#include <memory>

namespace Game
{

    namespace GUI
    {
        class Render;
    }

    inline namespace Utils
    {
        class Timer;
    }

    class Application final
    {
    public:
        Application() = delete;
        explicit Application(unsigned width, unsigned height, const char *title);
        ~Application();

        Application(const Application &) = delete;
        Application &operator=(const Application &) = delete;

        int Run() noexcept;

    private:
        void Init() noexcept;
        void Destroy() noexcept;

        const unsigned width_, height_;
        const char *title_;
        std::unique_ptr<GUI::Render> render_;
        std::shared_ptr<Timer> timer_;
    };

} // namespace Game
