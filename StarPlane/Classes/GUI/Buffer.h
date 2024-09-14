#pragma once


namespace Game
{
    namespace GUI
    {
        class Buffer
        {
        public:
            Buffer() = default;

            explicit Buffer(unsigned renderType) :
                renderType_(renderType)
            {
            }

            virtual ~Buffer() = default;


            virtual void Bind() const noexcept = 0;
            virtual int Size() const noexcept = 0;
            virtual unsigned Type() const noexcept = 0;
            virtual unsigned Id() const noexcept = 0;

            virtual void CreateBuffer(size_t size) noexcept
            {
                (void)size;
            }

            virtual void MoveBuffer(const void *data, size_t size) noexcept
            {
                (void)data;
                (void)size;
            }

            virtual unsigned RenderType() const noexcept
            {
                return renderType_;
            }

            virtual void ChangeRenderType(unsigned type) noexcept
            {
                renderType_ = type;
            }

            virtual void *AsArray() const noexcept
            {
                return nullptr;
            }

            template <class T>
            T *CastToArray() noexcept
            {
                return static_cast<T *>(AsArray());
            }

            template <class T>
            const T *CastToArray() const noexcept
            {
                return static_cast<T *>(AsArray());
            }

        protected:
            unsigned renderType_ = 0;
        };
    }
}
