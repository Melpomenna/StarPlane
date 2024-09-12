#pragma once
#include <cstdint>

namespace Game
{
    namespace GUI
    {
        enum class ShaderType : uint8_t
        {
            Vertex,
            Fragment,
            Non
        };

        class Shader
        {
        public:
            Shader() = default;
            explicit Shader(ShaderType, const char *);
            virtual ~Shader();

            virtual int Id() const noexcept;
            virtual void Bind() const noexcept;
            virtual void Destroy();
            ShaderType Type() const noexcept;
            const char *Error() const noexcept;

        private:
            void Init(const char *) noexcept;
            int GetTypeAsGLType() const noexcept;

        protected:
            int id_;
            ShaderType type_;
            char *error_;
        };
    }
}
