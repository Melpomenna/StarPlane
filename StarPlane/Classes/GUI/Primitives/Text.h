#pragma once

#include <GUI/Node.h>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <unordered_map>

namespace Game
{

    namespace GUI
    {

        class Text final : public Node
        {
        public:
            struct Character final
            {
                glm::ivec2 Size;
                glm::ivec2 Bearing;
                unsigned int TextureId;
                unsigned int Advanced;
            };

            Text();
            Text(std::string &&);
            ~Text() override;

            void SetFont(std::string &&) noexcept;

            void Bind(unsigned slot = 0) noexcept override;
            void Draw() noexcept override;
            void Unbind() noexcept override;
            unsigned RenderMode() const noexcept override;
            int IndexCount() const noexcept override;
            int VertexCount() const noexcept override;
            unsigned ElementType() const noexcept override;
            unsigned IndexElementType() const noexcept override;
            void SetColorFor(const void *) override;
            void Move(double, double) noexcept override;
            void SetPos(double, double) noexcept override;
            Position2D GetPos() const noexcept override;
            Size2D Size() const noexcept override;
            void Resize(Size2D) noexcept override;
            void StoreBuffers(const void *, size_t, const void *, size_t) override;
            void LoadTexture(const char *) noexcept override;
            void StoreTextureBuffer(const void *, size_t) noexcept override;
            void Rotate(double) override;

            void SetFontSize(unsigned) noexcept;
            unsigned GetFontSize() const noexcept;

            std::string &GetString() noexcept;
            const std::string &GetString() const noexcept;

            void SetString(std::string &&) noexcept;
            void SetScale(double) noexcept;
            double GetScale() const noexcept;

        private:
            void InitFT() noexcept;

        private:
            Position2D pos_;
            Size2D size_;
            unsigned fontSize_;
            double scale_ = 1;
            std::string fontName_;
            std::string text_;
            FT_Library ft_;
            FT_Face fontFace_;
            std::unordered_map<char, Character> characters_;
        };

    } // namespace GUI
} // namespace Game
