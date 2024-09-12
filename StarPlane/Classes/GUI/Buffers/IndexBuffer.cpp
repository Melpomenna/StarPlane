#include "IndexBuffer.h"

#include <GL/glew.h>

namespace Game
{
    namespace GUI
    {
        IndexBuffer::IndexBuffer() :
            data_(nullptr), size_(0), ibo_(0)
        {
            glGenBuffers(1, &ibo_);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_);
        }

        unsigned IndexBuffer::Id() const noexcept
        {
            return ibo_;
        }

        void IndexBuffer::Bind() const noexcept
        {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLsizeiptr>(sizeof(DataType) * size_), data_,
                         renderType_);
        }

        unsigned IndexBuffer::Type() const noexcept
        {
            return GL_UNSIGNED_INT;
        }

        int IndexBuffer::Size() const noexcept
        {
            return size_;
        }


        IndexBuffer::~IndexBuffer()
        {

            delete[] data_;
            data_ = nullptr;
            size_ = 0;
            ibo_ = -1;
        }


    }
}
