#include "ShaderProgram.h"

#include <GL/glew.h>

#include <GUI/Shader.h>
#include <GUI/Support.h>

#include <Utils/Config.h>

namespace Game
{
    namespace GUI
    {
        ShaderProgram::ShaderProgram() :
            id_(0)
        {
        }

        ShaderProgram::ShaderProgram(const char *vertexShader, const char *fragmentShader) :
            ShaderProgram()
        {
            Compile(vertexShader, fragmentShader);
        }

        void ShaderProgram::Bind() const noexcept
        {
            if (id_ == -1)
            {
#if !defined(NDEBUG)
#if defined(_WIN32)
                __debugbreak();
#else
                assert(false);
#endif
#endif
            }

            glUseProgram(id_);
        }

        int ShaderProgram::Id() const noexcept
        {
            return id_;
        }

        void ShaderProgram::Compile(const char *vertexShader, const char *fragmentShader) noexcept
        {
            const char *vertexBuffer = ReadFile(vertexShader);
            const char *fragmentBuffer = ReadFile(fragmentShader);
            vertexShader_ = std::make_shared<Shader>(ShaderType::Vertex, vertexBuffer);
            fragmentShader_ = std::make_shared<Shader>(ShaderType::Fragment, fragmentBuffer);

            APP_LOG(vertexBuffer);
            APP_LOG(fragmentBuffer);


            if (vertexShader_->Error() || fragmentShader_->Error())
            {
                APP_LOG(vertexShader_->Error());
                APP_LOG(fragmentShader_->Error());
#if !defined(NDEBUG)
#if defined(_WIN32)
                __debugbreak();
#else
                assert(false);
#endif
#endif
            }

            id_ = glCreateProgram();

            if (id_ == -1)
            {
#if !defined(NDEBUG)
#if defined(_WIN32)
                __debugbreak();
#else
                assert(false);
#endif
#endif
                return;
            }

            glAttachShader(id_, vertexShader_->Id());
            glAttachShader(id_, fragmentShader_->Id());
            glLinkProgram(id_);
            GLint result = 0;

            glGetProgramiv(id_, GL_LINK_STATUS, &result);

            if (result != GL_TRUE)
            {
                vertexShader_->Destroy();
                fragmentShader_->Destroy();
                glDeleteProgram(id_);
                id_ = -1;
#if !defined(NDEBUG)
#if defined(_WIN32)
                __debugbreak();
#else
                assert(false);
#endif
#endif
                return;
            }

            glValidateProgram(id_);
            glGetProgramiv(id_, GL_VALIDATE_STATUS, &result);

            if (result != GL_TRUE)
            {
                vertexShader_->Destroy();
                fragmentShader_->Destroy();
                glDeleteProgram(id_);
                id_ = -1;
#if !defined(NDEBUG)
#if defined(_WIN32)
                __debugbreak();
#else
                assert(false);
#endif
#endif
                return;
            }

            Bind();


            glDetachShader(id_, vertexShader_->Id());
            glDetachShader(id_, fragmentShader_->Id());
        }


        ShaderProgram::~ShaderProgram()
        {
            if (id_ == -1)
            {
                return;
            }

            glDeleteProgram(id_);
            id_ = -1;
        }


    }
}
