#pragma once

#include <atomic>
#include <chrono>

namespace Game
{

    inline namespace Utils
    {

        class Timer final
        {
        public:
            using TimeType = std::chrono::steady_clock;
            using TimePointType = TimeType::time_point;

            Timer();
            explicit Timer(TimePointType time);
            ~Timer() = default;

            Timer(const Timer &) noexcept;
            Timer &operator=(const Timer &) noexcept;

            Timer(Timer &&) noexcept;
            Timer &operator=(Timer &&) noexcept;

            double Mark() noexcept;
            double Peek() const noexcept;

        private:
            std::atomic<TimePointType> last_;
        };
    } // namespace Utils

} // namespace Game
