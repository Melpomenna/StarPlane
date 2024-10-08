#pragma once

#include <GUI/Buffer.h>

namespace Game
{

    namespace GUI
    {
        class TextColorBuffer final : public Buffer
        {
        public:
            using DataType = double;

        public:
            TextColorBuffer();
            TextColorBuffer(int = 0);
            ~TextColorBuffer() override;

            void CreateBuffer(size_t) noexcept override;
            void MoveBuffer(const void *, size_t) noexcept override;

            void Bind() const noexcept override;
            int Size() const noexcept override;
            unsigned Type() const noexcept override;
            unsigned Id() const noexcept override;

            void *AsArray() const noexcept override;

        private:
            size_t shift_ = 0;
            unsigned vbo_ = 0;
            const unsigned attribute_ = 0;
            DataType *data_;
            int size_;

        };
    } // namespace GUI
} // namespace Game
