#pragma once


#include <GUI/Buffer.h>

namespace Game
{

    namespace GUI
    {

        class TextVAOVBOBuffer final : public Buffer
        {
        public:
            TextVAOVBOBuffer();
            TextVAOVBOBuffer(int);
            ~TextVAOVBOBuffer() override = default;

            void Bind() const noexcept override;
            int Size() const noexcept override;
            unsigned Type() const noexcept override;
            unsigned Id() const noexcept override;

        private:
            unsigned vao_;
            unsigned vbo_;
            unsigned attribute_;
        };

    } // namespace GUI
} // namespace Game
