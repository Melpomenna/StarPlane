#pragma once

#pragma once

#include <GUI/Buffer.h>

namespace Game
{

    namespace GUI
    {

        class VertexBuffer final : public Buffer
        {
        public:
            using DataType = double;

        public:
            VertexBuffer();
            VertexBuffer(int attribute);
            VertexBuffer(int fragmentsCount, unsigned renderType, int attribute = 0);
            explicit VertexBuffer(size_t size, unsigned renderType, int attribute = 0);
            ~VertexBuffer() override;

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
            unsigned vbo_;
            int fragmentsCount_;
            const int attribute_;
        };
    } // namespace GUI

} // namespace Game
