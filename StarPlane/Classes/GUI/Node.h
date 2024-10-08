#pragma once

#include <memory>

#include <glm/glm.hpp>

#include <string>

namespace Game
{

    namespace GUI
    {

        class ShaderProgram;
        class Buffer;
        class Texture;

        struct Position2D
        {
            double x;
            double y;
        };

        struct Size2D
        {
            Size2D operator+(double) const noexcept;

            double width;
            double height;
        };

        class Node
        {
        public:
            struct glmMat4x4Wrapper
            {
                glm::mat4x4 mat_ = glm::mat4x4(1);
                int uniformMatrixLocation = -1;
            };

            Node();
            explicit Node(const char *, const char *, unsigned);
            virtual ~Node();

            virtual void Bind(unsigned slot = 0) noexcept;
            virtual void Draw() noexcept;
            virtual void Unbind() noexcept;
            virtual unsigned RenderMode() const noexcept;
            virtual int IndexCount() const noexcept;
            virtual int VertexCount() const noexcept;
            virtual unsigned ElementType() const noexcept;
            virtual unsigned IndexElementType() const noexcept;
            virtual void FillColor(float, float, float, float a = 1) noexcept;
            virtual void FillColor(const char *) noexcept;
            virtual void SetColorFor(const void *);
            virtual void Update(double);
            virtual void Move(double, double) noexcept;
            virtual void SetPos(double, double) noexcept;
            virtual Position2D GetPos() const noexcept;
            virtual Size2D Size() const noexcept;
            virtual void Resize(Size2D) noexcept;
            virtual void StoreBuffers(const void *, size_t, const void *, size_t);
            virtual void SetModel(glm::mat4x4 &) noexcept;
            virtual void SetProjection(glm::mat4x4 &) noexcept;
            virtual void LoadTexture(const char *) noexcept;
            virtual void StoreTextureBuffer(const void *, size_t) noexcept;
            virtual void Rotate(double);

            std::shared_ptr<Texture> &GetTexture() noexcept;
            const std::shared_ptr<Texture> &GetTexture() const noexcept;

            bool IsAvailableForDestroy() const noexcept;
            void Destroy() noexcept;

            void SetName(std::string &&) noexcept;
            const std::string &GetName() const noexcept;

            virtual bool IsVisible() const noexcept;
            virtual void SetVisible(bool) noexcept;

        protected:
            std::shared_ptr<ShaderProgram> program_;
            std::shared_ptr<Buffer> vertexBuffer_;
            std::shared_ptr<Buffer> colorBuffer_;
            std::shared_ptr<Buffer> indexBuffer_;
            std::shared_ptr<Texture> texture_;
            glmMat4x4Wrapper model_, projection_;
            std::string name_;
            bool isVisible_ = true;

        private:
            bool availableForDestroy_ = false;
        };
    } // namespace GUI

} // namespace Game
