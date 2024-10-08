#include "TextColorBuffer.h"

#include <algorithm>
#include <cstring>
#include <new>
#include <GL/glew.h>

namespace Game
{
    namespace GUI
    {

        TextColorBuffer::TextColorBuffer() :
            data_(nullptr), size_(0)
        {
            glGenBuffers(1, &vbo_);
            glBindBuffer(GL_ARRAY_BUFFER, vbo_);
        }

        TextColorBuffer::TextColorBuffer(const int attribute) :
            attribute_(attribute), data_(nullptr), size_(0)
        {
            glGenBuffers(1, &vbo_);
            glBindBuffer(GL_ARRAY_BUFFER, vbo_);
        }

        void TextColorBuffer::CreateBuffer(const size_t size) noexcept
        {
            if (size_ == size)
            {
                return;
            }
            DataType *ptr = ::new(std::nothrow) DataType[size];
            if (!ptr)
            {
                return;
            }
            if (data_)
            {
                memcpy(ptr, data_, std::min(size_, static_cast<int>(size)) * sizeof(DataType));
            }
            ::delete[] data_;
            data_ = ptr;
            size_ = static_cast<int>(size);
        }

        void TextColorBuffer::MoveBuffer(const void *data, const size_t size) noexcept
        {

            if (size == 0)
            {
                shift_ = 0;
            }
            shift_ += size;
        }

        unsigned TextColorBuffer::Id() const noexcept
        {
            return vbo_;
        }

        void TextColorBuffer::Bind() const noexcept
        {
            glBindBuffer(GL_ARRAY_BUFFER, vbo_);
            glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(sizeof(DataType) * 24),
                         data_+shift_*24,
                         GL_DYNAMIC_DRAW);
            glVertexAttribPointer(attribute_, 4, Type(), GL_FALSE,
                                  static_cast<GLsizei>(sizeof(DataType)) * 4, nullptr);
            glEnableVertexAttribArray(attribute_);
        }

        unsigned TextColorBuffer::Type() const noexcept
        {
            return GL_DOUBLE;
        }

        int TextColorBuffer::Size() const noexcept
        {
            return size_;
        }

        void *TextColorBuffer::AsArray() const noexcept
        {
            return data_;
        }


        TextColorBuffer::~TextColorBuffer()
        {

            delete[] data_;
            data_ = nullptr;
            size_ = 0;
            vbo_ = -1;
        }


    }
}
