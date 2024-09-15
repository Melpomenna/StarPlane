#pragma once

#include <memory>

#include <glm/glm.hpp>

namespace Game
{

    namespace GUI
    {

        class ShaderProgram;
        class Buffer;
        class Texture;

        class Node
        {
        public:
            struct glmMat4x4Wrapper
            {
                glm::mat4x4 mat_ = glm::mat4x4(1);
                int uniformMatrixLocation = -1;
            };

            Node() = default;
            explicit Node(const char *vertexShader, const char *fragmentShader, unsigned renderType);
            virtual ~Node() = default;

            virtual void Bind() noexcept;
            virtual unsigned RenderMode() const noexcept;
            virtual int IndexCount() const noexcept;
            virtual int VertexCount() const noexcept;
            virtual unsigned ElementType() const noexcept;
            virtual unsigned IndexElementType() const noexcept;
            virtual void FillColor(float r, float g, float b, float a = 1) noexcept;
            virtual void SetColorFor(const void *color);
            virtual void Update(double dt);
            virtual void Move(double x, double y) noexcept;
            virtual void SetPos(double x, double y) noexcept;
            virtual void StoreBuffers(const void *vertex, size_t vSize, const void *indexBuffer, size_t iSize);
            virtual void SetModel(glm::mat4x4 &) noexcept;
            virtual void SetProjection(glm::mat4x4 &) noexcept;
            virtual void LoadTexture(const char *) noexcept;
            virtual void StoreTextureBuffer(const void *buffer, size_t size) noexcept;

            std::shared_ptr<Texture> &GetTexture() noexcept;
            const std::shared_ptr<Texture> &GetTexture() const noexcept;

        protected:
            std::shared_ptr<ShaderProgram> program_;
            std::shared_ptr<Buffer> vertexBuffer_;
            std::shared_ptr<Buffer> colorBuffer_;
            std::shared_ptr<Buffer> indexBuffer_;
            std::shared_ptr<Texture> texture_;
            glmMat4x4Wrapper model_, projection_;
        };
    } // namespace GUI

} // namespace Game
