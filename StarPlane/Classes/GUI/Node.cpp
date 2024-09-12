#include "Node.h"


#include <GL/glew.h>
#include <GUI/ShaderProgram.h>
#include <GUI/Buffers/VertexBuffer.h>
#include <GUI/Buffers/IndexBuffer.h>

namespace Game
{
    namespace GUI
    {

        Node::Node(const char *vertexShader, const char *fragmentShader)
        {
            program_ = std::make_shared<ShaderProgram>(vertexShader, fragmentShader);
            vertexBuffer_ = std::make_shared<VertexBuffer>();
            indexBuffer_ = std::make_shared<IndexBuffer>();
        }

        void Node::Bind() noexcept
        {
            program_->Bind();
            vertexBuffer_->Bind();
            indexBuffer_->Bind();
        }

        unsigned Node::ElementType() const noexcept
        {
            return vertexBuffer_->Type();
        }


        int Node::IndexCount() const noexcept
        {
            return indexBuffer_->Size();
        }

        unsigned Node::RenderMode() const noexcept
        {
            return GL_TRIANGLES;
        }

        void Node::SetColor(float r, float g, float b, float a) noexcept
        {
            if (color_.uniformColorLocation == -1)
            {
                const int location = glGetUniformLocation(program_->Id(), "u_color");
                color_.uniformColorLocation = location;
            }

            if (color_.uniformColorLocation == -1)
            {
                return;
            }
            color_.c_ = {r, g, b, a};
            glUniform4d(color_.uniformColorLocation, r, g, b, a);
        }

        void Node::Update(double dt)
        {
            (void)dt;
        }


    }
}
