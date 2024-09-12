#pragma once

#include <memory>

namespace Game
{
    namespace GUI
    {

        class Shader;

        class ShaderProgram
        {
        public:
            ShaderProgram() = default;
            explicit ShaderProgram(const char *vertexShader, const char *fragmentShader);
            virtual ~ShaderProgram();

            virtual void Bind() const noexcept;
            virtual int Id() const noexcept;

        protected:
            virtual void Compile(const char *vertexShader, const char *fragmentShader) noexcept;

        protected:
            std::shared_ptr<Shader> vertexShader_, fragmentShader_;
            int id_;
        };
    } // namespace GUI

} // namespace Game
