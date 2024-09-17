#include "VertexBuffer.h"

#include <cstring>
#include <GL/glew.h>

#include <algorithm>

namespace Game
{
    namespace GUI
    {
        VertexBuffer::VertexBuffer() :
            data_(nullptr), size_(0), vbo_(0), fragmentsCount_(2), attribute_(0)
        {
            glGenBuffers(1, &vbo_);
            glBindBuffer(GL_ARRAY_BUFFER, vbo_);
        }

        VertexBuffer::VertexBuffer(const int attribute) :
            data_(nullptr), size_(0), vbo_(0), fragmentsCount_(2), attribute_(attribute)
        {
            glGenBuffers(1, &vbo_);
            glBindBuffer(GL_ARRAY_BUFFER, vbo_);
        }


        VertexBuffer::VertexBuffer(const int fragmentsCount, const unsigned renderType, const int attribute) :
            VertexBuffer(attribute)
        {
            renderType_ = renderType;
            fragmentsCount_ = fragmentsCount;
        }

        VertexBuffer::VertexBuffer(const size_t size, const unsigned renderType, const int attribute) :
            VertexBuffer(attribute)
        {
            renderType_ = renderType;
            CreateBuffer(size);
        }

        void VertexBuffer::CreateBuffer(const size_t size) noexcept
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

        void VertexBuffer::MoveBuffer(const void *data,const size_t size) noexcept
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

        unsigned VertexBuffer::Id() const noexcept
        {
            return vbo_;
        }

        void VertexBuffer::Bind() const noexcept
        {
            glBindBuffer(GL_ARRAY_BUFFER, vbo_);
            glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(sizeof(DataType) * size_), data_, renderType_);
            glVertexAttribPointer(attribute_, fragmentsCount_, Type(), GL_FALSE,
                                  static_cast<GLsizei>(sizeof(DataType)) * fragmentsCount_, nullptr);
            glEnableVertexAttribArray(attribute_);
        }

        unsigned VertexBuffer::Type() const noexcept
        {
            return GL_DOUBLE;
        }

        int VertexBuffer::Size() const noexcept
        {
            return size_;
        }

        void *VertexBuffer::AsArray() const noexcept
        {
            return data_;
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
