#include "ShaderProgram.h"

#include <GL/glew.h>

#include <GUI/Shader.h>
#include <GUI/Support.h>

#include <string>

namespace Game
{
    namespace GUI
    {
        ShaderProgram::ShaderProgram(const char *vertexShader, const char *fragmentShader)
        {
            Compile(vertexShader, fragmentShader);
        }

        void ShaderProgram::Bind() const noexcept
        {
            glUseProgram(id_);
        }

        int ShaderProgram::Id() const noexcept
        {
            return id_;
        }

        void ShaderProgram::Compile(const char *vertexShader, const char *fragmentShader) noexcept
        {
            id_ = glCreateProgram();
            const char *vertexBuffer = ReadFile(vertexShader);
            const char *fragmentBuffer = ReadFile(fragmentShader);
            vertexShader_ = std::make_shared<Shader>(ShaderType::Vertex, vertexBuffer);
            fragmentShader_ = std::make_shared<Shader>(ShaderType::Fragment, fragmentBuffer);
            glAttachShader(id_, vertexShader_->Id());
            glAttachShader(id_, fragmentShader_->Id());
            glLinkProgram(id_);
        }


        ShaderProgram::~ShaderProgram()
        {
            if (id_ == -1)
            {
                return;
            }

            glDetachShader(id_, vertexShader_->Id());
            glDetachShader(id_, fragmentShader_->Id());
            vertexShader_->Destroy();
            fragmentShader_->Destroy();
            glDeleteProgram(id_);
            id_ = -1;
        }


    }
}
