#include "IndexBuffer.h"

#include <cstring>
#include <GL/glew.h>

#include <algorithm>

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

        IndexBuffer::IndexBuffer(size_t size, unsigned renderType) :
            IndexBuffer()
        {
            renderType_ = renderType;
            CreateBuffer(size);
        }

        void IndexBuffer::CreateBuffer(size_t size) noexcept
        {
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

        void IndexBuffer::MoveBuffer(const void *data, size_t size) noexcept
        {

            if (!data)
            {
                return;
            }

            if (!data_ || static_cast<size_t>(size_) != size)
            {
                CreateBuffer(size);
            }

            if (size_ == static_cast<int>(size) && data_)
            {
                memcpy(data_, data, size_ * sizeof(DataType));
            }
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

        void *IndexBuffer::AsArray() const noexcept
        {
            return data_;
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
