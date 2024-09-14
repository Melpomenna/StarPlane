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
        class Optional
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

            explicit Optional(ValueType &&value) :
                value_(std::forward<ValueType>(value)), hasValue_(true)
            {
            }

            virtual ~Optional() = default;

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
                return has_value() && other.has_value() && value_ && other.get();
            }

            bool operator!=(const Optional &other) const noexcept
            {
                return !(*this == other);
            }

            Optional &operator=(ValueType &&other)
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

            ValueType &get()
            {
                if (!hasValue_)
                {
                    throw std::runtime_error("Bad optional access!");
                }
                return value_;
            }

            const ValueType &get() const
            {
                if (!hasValue_)
                {
                    throw std::runtime_error("Bad optional access!");
                }
                return value_;
            }

            bool has_value() const noexcept
            {
                return hasValue_;
            }

            void reset()
            {
                hasValue_ = false;
            }

        private:
            ValueType value_;
            bool hasValue_;
        };
    }
}
