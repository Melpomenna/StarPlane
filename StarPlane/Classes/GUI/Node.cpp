#include <Utils/Config.h>

#include "Node.h"


#include <GUI/Render.h>
#include <GUI/ShaderProgram.h>
#include <GUI/Buffers/VertexBuffer.h>
#include <GUI/Buffers/IndexBuffer.h>
#include <GUI/Texture.h>

#include <glm/gtc/type_ptr.inl>

#include <immintrin.h>
#include <string>


namespace Game
{
    namespace GUI
    {

        Node::Node()
        {
            Render::ResolveRender()->AddNode(this);
        }

        Node::~Node()
        {
            Destroy();
        }


        Node::Node(const char *vertexShader, const char *fragmentShader, unsigned renderType) :
            Node()
        {
            program_ = std::make_shared<ShaderProgram>(vertexShader, fragmentShader);
            vertexBuffer_ = std::make_shared<VertexBuffer>();
            indexBuffer_ = std::make_shared<IndexBuffer>();

            auto colorLocation = glGetUniformLocation(program_->Id(), "color");

            if (colorLocation == -1)
            {
                colorLocation = 1;
            }

            colorBuffer_ = std::make_shared<VertexBuffer>(4, renderType, colorLocation);
            texture_ = std::make_shared<Texture>(program_->Id(), renderType);
            vertexBuffer_->ChangeRenderType(renderType);
            indexBuffer_->ChangeRenderType(renderType);
        }

        void Node::Bind(const unsigned slot) noexcept
        {
            program_->Bind();
            texture_->Bind(slot);
            vertexBuffer_->Bind();
            colorBuffer_->Bind();
            indexBuffer_->Bind();
        }

        void Node::Draw() noexcept
        {
            glDrawElements(RenderMode(), IndexCount(), IndexElementType(), nullptr);
        }


        void Node::Unbind() noexcept
        {
            texture_->Unbind();
        }


        unsigned Node::ElementType() const noexcept
        {
            return vertexBuffer_->Type();
        }


        int Node::IndexCount() const noexcept
        {
            return indexBuffer_->Size();
        }

        unsigned Node::IndexElementType() const noexcept
        {
            return indexBuffer_->Type();
        }

        int Node::VertexCount() const noexcept
        {
            return vertexBuffer_->Size();
        }


        unsigned Node::RenderMode() const noexcept
        {
            return GL_TRIANGLES;
        }

        void Node::FillColor(const float r, const float g, const float b, const float a) noexcept
        {
            auto data = colorBuffer_->CastToArray<double>();
            if (!data)
            {
                colorBuffer_->CreateBuffer(static_cast<size_t>(vertexBuffer_->Size()) * 2);
                data = colorBuffer_->CastToArray<double>();
            }
            const auto size = colorBuffer_->Size();
            double color[] = {
                r, g, b, a
            };

            __m256d i_color = _mm256_load_pd(color);
            for (int i = 0; i + 4 <= size; i += 4)
            {
                __m256d selfColor = _mm256_load_pd(data + i);
                selfColor = _mm256_xor_pd(selfColor, selfColor);
                __m256d result = _mm256_add_pd(selfColor, i_color);
                _mm256_store_pd(data + i, result);
#if defined(ENABLE_LOG)
                const auto dr = "\nr:" + std::to_string(data[i]) + " ,g:";
                const auto dg = std::to_string(data[i + 1]) + " ,b:";
                const auto db = std::to_string(data[i + 2]) + " ,a:";
                const auto da = std::to_string(data[i + 3]) + "\n";
                const auto outStr = dr + dg + db + da;
                APP_LOG(outStr.c_str());
#endif
            }
        }

        void Node::FillColor(const char *hexColor) noexcept
        {
            if (hexColor == nullptr)
            {
                return;
            }

            std::string shex{hexColor};
            FillColor(static_cast<float>(std::stoi(shex.substr(1, 2), nullptr, 16)) / 255.0f,
                      static_cast<float>(std::stoi(shex.substr(3, 2), nullptr, 16)) / 255.0f,
                      static_cast<float>(std::stoi(shex.substr(5, 2), nullptr, 16)) / 255.0f, 1.0);
        }


        void Node::SetColorFor(const void *color)
        {
            if (!colorBuffer_->AsArray())
            {
                colorBuffer_->CreateBuffer(static_cast<size_t>(vertexBuffer_->Size()) * 2);
            }
            colorBuffer_->MoveBuffer(color, colorBuffer_->Size());
        }


        void Node::Update(double dt)
        {
            (void)dt;
        }

        void Node::Move(double x, double y) noexcept
        {
            VertexBuffer::DataType *vertex = vertexBuffer_->CastToArray<double>();
            const auto size = vertexBuffer_->Size();

            for (auto i = 0; i + 2 < size; i += 2)
            {
                vertex[i] += x;
                vertex[i + 1] += y;
            }
        }

        void Node::SetPos(double, double) noexcept
        {

        }


        void Node::StoreBuffers(const void *vertex, const size_t vSize, const void *indexBuffer, const size_t iSize)
        {
            vertexBuffer_->MoveBuffer(vertex, vSize);
            indexBuffer_->MoveBuffer(indexBuffer, iSize);
        }

        void Node::SetModel(glm::mat4x4 &model) noexcept
        {
            if (model_.uniformMatrixLocation == -1)
            {
                model_.uniformMatrixLocation = glGetUniformLocation(program_->Id(), "u_model");
            }

            if (model_.uniformMatrixLocation == -1)
            {
                return;
            }

            model_.mat_ = model;
            glUniformMatrix4fv(model_.uniformMatrixLocation, 1, GL_FALSE, glm::value_ptr(model_.mat_));
        }

        void Node::SetProjection(glm::mat4x4 &projection) noexcept
        {
            if (projection_.uniformMatrixLocation == -1)
            {
                projection_.uniformMatrixLocation = glGetUniformLocation(program_->Id(), "u_projection");
            }

            if (projection_.uniformMatrixLocation == -1)
            {
                return;
            }

            projection_.mat_ = projection;
            glUniformMatrix4fv(projection_.uniformMatrixLocation, 1, GL_FALSE, glm::value_ptr(projection_.mat_));
        }

        void Node::LoadTexture(const char *texture) noexcept
        {
            texture_->LoadTexture(texture);
        }

        void Node::StoreTextureBuffer(const void *buffer, const size_t size) noexcept
        {
            texture_->StoreBuffer(buffer, size);
        }

        void Node::Rotate(const double angle)
        {
            texture_->Rotate(angle);
        }


        std::shared_ptr<Texture> &Node::GetTexture() noexcept
        {
            return texture_;
        }

        const std::shared_ptr<Texture> &Node::GetTexture() const noexcept
        {
            return texture_;
        }

        bool Node::IsAvailableForDestroy() const noexcept
        {
            return availableForDestroy_;
        }

        void Node::Destroy() noexcept
        {
            availableForDestroy_ = true;
        }

        void Node::SetName(std::string &&name) noexcept
        {
            name_ = std::move(name);
        }

        const std::string &Node::GetName() const noexcept
        {
            return name_;
        }

        bool Node::IsVisible() const noexcept
        {
            return isVisible_;
        }

        void Node::SetVisible(const bool value) noexcept
        {
            isVisible_ = value;
        }

        Position2D Node::GetPos() const noexcept
        {
            return {0, 0};
        }

        Size2D Node::Size() const noexcept
        {
            return {0, 0};
        }

        void Node::Resize(Size2D) noexcept
        {

        }

        Size2D Size2D::operator+(const double value) const noexcept
        {
            return {width + value, height + value};
        }

    }
}
