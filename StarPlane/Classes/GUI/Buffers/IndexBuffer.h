#pragma once

#include <GUI/Buffer.h>

namespace Game
{

    namespace GUI
    {

        class IndexBuffer final : public Buffer
        {
        public:
            using DataType = unsigned;

        public:
            IndexBuffer();
            explicit IndexBuffer(size_t, unsigned);
            ~IndexBuffer() override;


            void CreateBuffer(size_t) noexcept override;
            void MoveBuffer(const void *, size_t) noexcept override;

            void Bind() const noexcept override;
            int Size() const noexcept override;
            unsigned Type() const noexcept override;
            unsigned Id() const noexcept override;
            void *AsArray() const noexcept override;

        private:
            DataType *data_;
            int size_;
            unsigned ibo_;

        };
    } // namespace GUI

} // namespace Game
