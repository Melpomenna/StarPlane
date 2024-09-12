#include "Shader.h"

#include <string>
#include <GL/glew.h>

namespace Game
{
    namespace GUI
    {
        Shader::Shader(ShaderType type, const char *src) :
            type_(type), error_(nullptr)
        {
            Init(src);
        }

        int Shader::Id() const noexcept
        {
            return id_;
        }

        void Shader::Bind() const noexcept
        {

        }


        ShaderType Shader::Type() const noexcept
        {
            return type_;
        }

        const char *Shader::Error() const noexcept
        {
            return error_;
        }


        Shader::~Shader()
        {
            Destroy();
        }

        void Shader::Destroy()
        {
            delete[] error_;
            error_ = nullptr;
            if (id_ == -1)
            {
                return;
            }

            glDeleteShader(id_);
            id_ = -1;
            delete[] error_;
        }

        void Shader::Init(const char *src) noexcept
        {
            id_ = glCreateShader(GetTypeAsGLType());
            glShaderSource(id_, 1, &src, nullptr);
            glCompileShader(id_);

            int result{};

            glGetShaderiv(id_, GL_COMPILE_STATUS, &result);
            if (result != GL_TRUE)
            {
                int length{};
                glGetShaderiv(id_, GL_INFO_LOG_LENGTH, &length);
                id_ = -1;

#if defined(_malloca)
                char *str = static_cast<char *>(_malloca(length));
#else
                char *str = new char[length];
#endif
                glGetShaderInfoLog(id_, length, &length, str);
                if (!str)
                {
                    return;
                }
                error_ = new char[length];
                memcpy(error_, str, length);
#if defined(_malloca)
                _freea(str);
#else
                delete[] str;
#endif
                id_ = -1;
            }


        }

        int Shader::GetTypeAsGLType() const noexcept
        {
            switch (type_)
            {
            case ShaderType::Vertex:
                return GL_VERTEX_SHADER;
            case ShaderType::Fragment:
                return GL_FRAGMENT_SHADER;
            default:
                return GL_FALSE;
            }

        }


    }
}
