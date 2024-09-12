#pragma once


namespace Game
{
    namespace GUI
    {
        class Buffer
        {
        public:
            Buffer() = default;
            virtual ~Buffer() = default;


            virtual void Bind() const noexcept = 0;
            virtual int Size() const noexcept = 0;
            virtual unsigned Type() const noexcept = 0;
            virtual unsigned Id() const noexcept = 0;

            virtual unsigned RenderType() const noexcept
            {
                return renderType_;
            }

            virtual void ChangeRenderType(unsigned type) noexcept
            {
                renderType_ = type;
            }

        protected:
            unsigned renderType_ = 0;
        };
    }
}
