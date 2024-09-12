#include "VertexBuffer.h"

#include <GL/glew.h>

namespace Game
{
    namespace GUI
    {
        VertexBuffer::VertexBuffer() :
            data_(nullptr), size_(0), vbo_(0), fragmentsCount_(2)
        {
            glGenBuffers(1, &vbo_);
            glBindBuffer(GL_ARRAY_BUFFER, vbo_);
        }

        VertexBuffer::VertexBuffer(int fragmentsCount) :
            VertexBuffer()
        {
            fragmentsCount_ = fragmentsCount;
        }


        unsigned VertexBuffer::Id() const noexcept
        {
            return vbo_;
        }

        void VertexBuffer::Bind() const noexcept
        {
            glBindBuffer(GL_ARRAY_BUFFER, vbo_);
            glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(sizeof(DataType) * size_), data_, renderType_);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, static_cast<GLint>(fragmentsCount_), GL_DOUBLE, GL_FALSE,
                                  static_cast<GLsizei>(sizeof(DataType) * fragmentsCount_), nullptr);
        }

        unsigned VertexBuffer::Type() const noexcept
        {
            return GL_UNSIGNED_INT;
        }

        int VertexBuffer::Size() const noexcept
        {
            return size_;
        }


        VertexBuffer::~VertexBuffer()
        {

            delete[] data_;
            data_ = nullptr;
            size_ = 0;
            vbo_ = -1;
        }


    } // namespace GUI
} // namespace Game
