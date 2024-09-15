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
            explicit Texture(unsigned shaderProgramId, unsigned renderType);
            explicit Texture(unsigned shaderProgramId, unsigned renderType, const char *filePath);
            virtual ~Texture();

            void LoadTexture(const char *filePath);

            void Bind(unsigned int slot = 0) const noexcept;
            void Unbind() noexcept;

            void StoreBuffer(const void *ptr, size_t size) noexcept;

        private:
            void Read(const char *);

        private:
            std::shared_ptr<Buffer> textureCoords_;
            char *filePath_;
            size_t fileLen_;
            unsigned char *buffer_;
            int width_, height_, size_;
            unsigned id_;
            unsigned shaderProgramId_;
        };

    } // namespace GUI
} // namespace Game
