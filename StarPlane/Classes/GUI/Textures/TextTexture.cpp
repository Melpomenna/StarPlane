#include "TextTexture.h"

#include <GL/glew.h>

namespace Game
{
    namespace GUI
    {
        TextTexture::TextTexture(const unsigned shaderProgramId) :
            shaderProgramId_(shaderProgramId)
        {
        }


        void TextTexture::LoadTexture(const char *)
        {
        }


        void TextTexture::Bind(const unsigned int slot) const noexcept
        {
            glActiveTexture(GL_TEXTURE0 + slot);

            const int location = glGetUniformLocation(shaderProgramId_, "u_texture");

            if (location == -1)
            {
                return;
            }

            glUniform1i(location, static_cast<GLint>(slot));

        }

        void TextTexture::StoreBuffer(const void *ptr, const size_t size) noexcept
        {

        }

        double TextTexture::Angle() const noexcept
        {
            return 0;
        }

        void TextTexture::Rotate(const double)
        {

        }

    }
}
