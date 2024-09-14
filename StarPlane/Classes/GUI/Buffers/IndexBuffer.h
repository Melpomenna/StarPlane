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
            explicit IndexBuffer(size_t size, unsigned renderType);
            ~IndexBuffer() override;


            void CreateBuffer(size_t size) noexcept override;
            void MoveBuffer(const void *data, size_t size) noexcept override;

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
