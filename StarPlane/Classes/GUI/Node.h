#pragma once

#include <memory>

#include <GUI/Color.h>

namespace Game
{

    namespace GUI
    {

        class ShaderProgram;
        class VertexBuffer;
        class IndexBuffer;

        class Node
        {
        public:
            Node() = default;
            explicit Node(const char *vertexShader, const char *fragmentShader);
            virtual ~Node() = default;

            virtual void Bind() noexcept;
            virtual unsigned RenderMode() const noexcept;
            virtual int IndexCount() const noexcept;
            virtual unsigned ElementType() const noexcept;
            virtual void SetColor(float r, float g, float b, float a = 1) noexcept;
            virtual void Update(double dt);

        protected:
            std::shared_ptr<ShaderProgram> program_;
            std::shared_ptr<VertexBuffer> vertexBuffer_;
            std::shared_ptr<IndexBuffer> indexBuffer_;
            internal::Color color_;
        };
    } // namespace GUI

} // namespace Game
