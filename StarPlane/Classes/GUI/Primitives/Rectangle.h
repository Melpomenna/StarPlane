#pragma once

#include <GUI/Node.h>

namespace Game
{

    namespace GUI
    {

        class Rectangle final : public Node
        {
        public:
            Rectangle() = delete;
            Rectangle(double, double);

            void StoreBuffers(const void *, size_t, const void *, size_t) override;

            void SetPos(double, double) noexcept override;
            void Move(double, double) noexcept override;

        private:
            double width_, height_;
            double currentPosX_, currentPosY_;
        };

    } // namespace GUI
} // namespace Game
