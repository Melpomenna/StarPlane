#pragma once
#include <stdexcept>

namespace Game
{
    inline namespace Utils
    {
        struct NullOpt
        {
        };

        template <class T>
        class Optional final
        {
        public:
            using ValueType = T;


            Optional() :
                hasValue_(false)
            {
            }

            Optional(NullOpt) :
                hasValue_(false)
            {
            }

            template <class Q>
            explicit Optional(Q &&value) :
                value_(std::forward<ValueType>(value)), hasValue_(true)
            {
            }

            ~Optional() = default;

            bool operator==(ValueType other) const noexcept
            {
                if (!hasValue_)
                {
                    return false;
                }
                return value_ == other;
            }

            bool operator!=(ValueType other) const noexcept
            {
                return !(*this == other);
            }

            bool operator==(NullOpt other) const noexcept
            {
                return hasValue_;
            }

            bool operator!=(NullOpt other) const noexcept
            {
                return !(*this == other);
            }

            bool operator==(const Optional &other) const noexcept
            {
                return HasValue() && other.HasValue() && value_ && other.Get();
            }

            bool operator!=(const Optional &other) const noexcept
            {
                return !(*this == other);
            }

            template <class Q>
            Optional &operator=(Q &&other)
            {
                hasValue_ = true;
                value_ = std::forward<ValueType>(other);
                return *this;
            }

            ValueType &operator*()
            {
                if (!hasValue_)
                {
                    throw std::runtime_error("Bad optional access!");
                }
                return value_;
            }

            const ValueType &operator*() const
            {
                if (!hasValue_)
                {
                    throw std::runtime_error("Bad optional access!");
                }
                return value_;
            }

            ValueType &Get()
            {
                if (!hasValue_)
                {
                    throw std::runtime_error("Bad optional access!");
                }
                return value_;
            }

            const ValueType &Get() const
            {
                if (!hasValue_)
                {
                    throw std::runtime_error("Bad optional access!");
                }
                return value_;
            }

            bool HasValue() const noexcept
            {
                return hasValue_;
            }

            void Reset()
            {
                hasValue_ = false;
            }

        private:
            ValueType value_;
            bool hasValue_;
        };
    }
}
