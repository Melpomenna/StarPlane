#include "Texture.h"

#include <GL/glew.h>

#include <ThirdParty/Include/stb_image.h>

#include <cstring>

#include <fstream>

#include <GUI/Buffers/VertexBuffer.h>

namespace Game
{
    namespace GUI
    {
        Texture::Texture(unsigned shaderProgramId, unsigned renderType) :
            filePath_(nullptr), fileLen_(), buffer_(nullptr), width_(), height_(), size_(), id_(0),
            shaderProgramId_(shaderProgramId)
        {
            auto textureCoordLocation = glGetUniformLocation(shaderProgramId_, "ti_color");

            if (textureCoordLocation == -1)
            {
                textureCoordLocation = 4;
            }

            textureCoords_ = std::make_shared<VertexBuffer>(2, renderType, textureCoordLocation);
            glGenBuffers(1, &id_);
            glBindTexture(GL_TEXTURE_2D, id_);

            const int location = glGetUniformLocation(shaderProgramId_, "u_texture");

            if (location == -1)
            {
                return;
            }

            glUniform1i(location, 0);

        }

        Texture::Texture(unsigned shaderProgramId, unsigned renderType, const char *filePath) :
            Texture(shaderProgramId, renderType)
        {
            LoadTexture(filePath);
        }


        void Texture::LoadTexture(const char *filePath)
        {
            Read(filePath);

            if (id_ == 0 || !buffer_)
            {
                return;
            }

            glBindTexture(GL_TEXTURE_2D, id_);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width_, height_, 0,
                         GL_RGBA, GL_UNSIGNED_BYTE, buffer_);
            glBindTexture(GL_TEXTURE_2D, 0);
        }


        void Texture::Bind(unsigned int slot) const noexcept
        {
            glActiveTexture(GL_TEXTURE0 + slot);
            glBindTexture(GL_TEXTURE_2D, id_);
            textureCoords_->Bind();
        }

        void Texture::Read(const char *filePath)
        {
            if (filePath_ && std::memcmp(filePath_, filePath, fileLen_) == 0)
            {
                return;
            }

            std::ifstream file{filePath};
            if (!file.is_open())
            {
                return;
            }

            const auto size = std::strlen(filePath) + 1;
            char *ptr = ::new char[size]();
            if (!ptr)
            {
                return;
            }

            ::delete[] filePath_;
            filePath_ = ptr;
            fileLen_ = size;
            std::memcpy(filePath_, filePath, size);

            int ignored;
            if (!buffer_)
            {
                stbi_image_free(buffer_);
            }
            buffer_ = stbi_load(filePath_, &width_, &height_, &ignored, 4);

        }

        void Texture::StoreBuffer(const void *ptr, size_t size) noexcept
        {
            textureCoords_->MoveBuffer(ptr, size);
        }


        void Texture::Unbind() noexcept
        {
            glBindTexture(GL_TEXTURE_2D, 0);
        }


        Texture::~Texture()
        {
            ::delete[] buffer_;
            buffer_ = nullptr;
            ::delete[] filePath_;
            filePath_ = nullptr;
            if (id_ == 0)
            {
                return;
            }
            glDeleteTextures(1, &id_);
            id_ = 0;
        }


    }
}
