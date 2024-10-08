#pragma once

#include <memory>

namespace Game
{

    inline namespace Utils
    {
        class Timer;
    }

    class Application final
    {
    public:
        Application() = delete;
        explicit Application(const unsigned width, const unsigned height, const char *title);
        ~Application();

        Application(const Application &) = delete;
        Application &operator=(const Application &) = delete;

        int Run() const noexcept;

    private:
        void Init() noexcept;
        void Destroy() noexcept;

        const unsigned width_, height_;
        const char *title_;
        std::shared_ptr<Timer> timer_;
    };

} // namespace Game
