#pragma once

#include <memory>

namespace Game
{

    namespace GUI
    {

        class Buffer;

        class Texture
        {
        public:
            Texture() = default;
            explicit Texture(unsigned, unsigned);
            explicit Texture(unsigned, unsigned, const char *);
            virtual ~Texture();

            virtual void LoadTexture(const char *);

            virtual void Bind(unsigned int slot = 0) const noexcept;
            virtual void Unbind() const noexcept;

            virtual void StoreBuffer(const void *, size_t) noexcept;

            virtual void Rotate(double);

            virtual double Angle() const noexcept;

        private:
            void Read(const char *);

        private:
            std::shared_ptr<Buffer> textureCoords_;
            char *filePath_ = nullptr;
            size_t fileLen_ = 0;
            unsigned char *buffer_ = nullptr;
            int width_ = 0, height_ = 0;
            unsigned id_ = 0;
            unsigned shaderProgramId_ = 0;
            double angle_ = 0;
        };

    } // namespace GUI
} // namespace Game
