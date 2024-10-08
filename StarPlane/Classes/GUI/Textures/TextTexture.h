#pragma once

#include <GUI/Texture.h>

namespace Game
{

    namespace GUI
    {

        class TextTexture final : public Texture
        {
        public:
            TextTexture(unsigned);
            ~TextTexture() override = default;

            void LoadTexture(const char *) override;

            void Bind(unsigned int slot = 0) const noexcept override;

            void StoreBuffer(const void *, size_t) noexcept override;

            void Rotate(double) override;

            double Angle() const noexcept override;

        private:
            unsigned shaderProgramId_;
        };
    }
} // namespace Game
