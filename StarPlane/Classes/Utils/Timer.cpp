#include "Timer.h"


namespace Game
{
    inline namespace Utils
    {
        Timer::Timer()
        {
            last_.store(TimeType::now());
        }

        Timer::Timer(const TimePointType time)
        {
            last_.store(time);
        }

        Timer::Timer(const Timer &other) noexcept
        {
            last_.store(other.last_.load());
        }

        Timer &Timer::operator=(const Timer &other) noexcept
        {
            if (this == &other)
            {
                return *this;
            }

            last_.store(other.last_.load());

            return *this;
        }

        Timer::Timer(Timer &&other) noexcept
        {
            last_.store(other.last_.load());
            other.last_.store(TimeType::now());
        }

        Timer &Timer::operator=(Timer &&other) noexcept
        {
            if (this == &other)
            {
                return *this;
            }

            last_.store(other.last_.load());
            other.last_.store(TimeType::now());

            return *this;
        }

        double Timer::Mark() noexcept
        {
            const auto old = last_.load();
            last_.store(TimeType::now());
            return std::chrono::duration<double>(last_.load() - old).count();
        }


        double Timer::Peek() const noexcept
        {
            return std::chrono::duration<double>(TimeType::now() - last_.load()).count();
        }


    }
}
