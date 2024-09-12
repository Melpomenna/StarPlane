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
            explicit VertexBuffer(int fragmentsCount);
            ~VertexBuffer() override;


            void Bind() const noexcept override;
            int Size() const noexcept override;
            unsigned Type() const noexcept override;
            unsigned Id() const noexcept override;

        private:
            DataType *data_;
            int size_;
            unsigned vbo_;
            int fragmentsCount_;
        };
    } // namespace GUI

} // namespace Game
