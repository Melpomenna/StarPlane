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
            Rectangle(double width, double height);

            void StoreBuffers(const void *vertex, size_t vSize, const void *indexBuffer, size_t iSize) override;

            void SetPos(double x, double y) noexcept override;
            void Move(double x, double y) noexcept override;

        private:
            double width_, height_;
            double currentPosX_, currentPosY_;
        };

    } // namespace GUI
} // namespace Game
