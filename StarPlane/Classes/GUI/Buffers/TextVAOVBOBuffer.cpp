#include "TextVAOVBOBuffer.h"

#include <GL/glew.h>

namespace Game
{
    namespace GUI
    {
        TextVAOVBOBuffer::TextVAOVBOBuffer() :
            attribute_(0)
        {

            glGenBuffers(1, &vbo_);
            glGenVertexArrays(1, &vao_);

            glBindVertexArray(vao_);
            glBindBuffer(GL_ARRAY_BUFFER, vbo_);

            glBufferData(GL_ARRAY_BUFFER, sizeof(GLdouble) * 24, nullptr, GL_DYNAMIC_DRAW);
            glEnableVertexAttribArray(attribute_);
            glVertexAttribPointer(attribute_, 4, GL_DOUBLE, GL_FALSE, 4 * sizeof(GLdouble), nullptr);

            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);

        }

        TextVAOVBOBuffer::TextVAOVBOBuffer(const int attribute) :
            TextVAOVBOBuffer()
        {
            attribute_ = attribute;

            glBufferData(GL_ARRAY_BUFFER, sizeof(GLdouble) * 16, nullptr, GL_DYNAMIC_DRAW);
            glEnableVertexAttribArray(attribute_);
            glVertexAttribPointer(attribute_, 4, GL_DOUBLE, GL_FALSE, 4 * sizeof(GLdouble), nullptr);

            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
        }


        void TextVAOVBOBuffer::Bind() const noexcept
        {
            glBindVertexArray(vao_);
        }

        int TextVAOVBOBuffer::Size() const noexcept
        {
            return 24;
        }

        unsigned TextVAOVBOBuffer::Type() const noexcept
        {
            return GL_DOUBLE;
        }

        unsigned TextVAOVBOBuffer::Id() const noexcept
        {
            return vbo_;
        }
    }
}
