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

            void LoadTexture(const char *);

            void Bind(unsigned int slot = 0) const noexcept;
            void Unbind() const noexcept;

            void StoreBuffer(const void *, size_t) noexcept;

        private:
            void Read(const char *);

        private:
            std::shared_ptr<Buffer> textureCoords_;
            char *filePath_;
            size_t fileLen_;
            unsigned char *buffer_;
            int width_, height_;
            unsigned id_;
            unsigned shaderProgramId_;
        };

    } // namespace GUI
} // namespace Game
