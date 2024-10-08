#include "Text.h"

#include <Utils/Config.h>


#include <GL/glew.h>

#include <GUI/ShaderProgram.h>
#include <GUI/Textures/TextTexture.h>
#include <GUI/Buffers/TextVAOVBOBuffer.h>
#include <GUI/Buffers/TextColorBuffer.h>

namespace Game
{
    namespace GUI
    {
        Text::Text() :
            pos_({0, 0}),
            size_({0, 0}),
            ft_(nullptr),
            fontFace_(nullptr)
        {
            InitFT();
            program_ = std::make_shared<ShaderProgram>(SHADERS_PATH(TextVertex.vert),SHADERS_PATH(TextFragment.frag));

            auto colorLocation = glGetUniformLocation(program_->Id(), "color");

            if (colorLocation == -1)
            {
                colorLocation = 1;
            }

            texture_ = std::make_shared<TextTexture>(program_->Id());
            vertexBuffer_ = std::make_shared<TextVAOVBOBuffer>();
            colorBuffer_ = std::make_shared<TextColorBuffer>(colorLocation);
        }

        Text::Text(std::string &&fontName) :
            Text()
        {
            SetFont(std::move(fontName));
        }

        Text::~Text()
        {
            FT_Done_Face(fontFace_);
            FT_Done_FreeType(ft_);
            fontFace_ = nullptr;
            ft_ = nullptr;
        }

        void Text::SetFont(std::string &&fontName) noexcept
        {
            if (fontName_ != fontName)
            {
                FT_Face newFace;
                if (FT_New_Face(ft_, fontName.c_str(), 0, &newFace))
                {
                    return;
                }

                FT_Done_Face(fontFace_);
                fontFace_ = newFace;
            }
            else
            {
                return;
            }

            characters_.clear();
            fontName_ = std::move(fontName);

            constexpr GLubyte maxChar = static_cast<GLubyte>((1 << (sizeof(GLubyte) * 8)) - 1);
            for (GLubyte c = 0; c < maxChar; ++c)
            {
                if (FT_Load_Char(fontFace_, c,FT_LOAD_RENDER))
                {
                    APP_LOG(("Text: cannot load sym:" + std::to_string(c)).c_str());
                    continue;
                }

                GLuint texture;
                glGenTextures(1, &texture);
                glBindTexture(GL_TEXTURE_2D, texture);

                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

                glTexImage2D(GL_TEXTURE_2D,
                             0,
                             GL_RED,
                             static_cast<GLsizei>(fontFace_->glyph->bitmap.width),
                             static_cast<GLsizei>(fontFace_->glyph->bitmap.rows),
                             0,
                             GL_RED,
                             GL_UNSIGNED_BYTE,
                             fontFace_->glyph->bitmap.buffer);

                glGenerateMipmap(GL_TEXTURE_2D);

                Character character = {
                    glm::ivec2(fontFace_->glyph->bitmap.width, fontFace_->glyph->bitmap.rows),
                    glm::ivec2(fontFace_->glyph->bitmap_left, fontFace_->glyph->bitmap_top),
                    texture,
                    static_cast<unsigned int>(fontFace_->glyph->advance.x)
                };
                characters_.insert({c, character});
            }
        }

        void Text::Bind(const unsigned slot) noexcept
        {
            program_->Bind();
            texture_->Bind(slot);
            vertexBuffer_->Bind();
        }


        void Text::Draw() noexcept
        {
            auto x = pos_.x;
            const auto y = pos_.y;

            const auto start = x;
            int height = 0;

            for (const auto &c : text_)
            {
                colorBuffer_->Bind();
                const Character ch = characters_[c];

                const GLdouble xPos = x + ch.Bearing.x * scale_;
                const GLdouble yPos = y - (ch.Size.y - ch.Bearing.y) * scale_;

                const GLdouble w = ch.Size.x * scale_;
                const GLdouble h = ch.Size.y * scale_;
                height = ch.Size.y > height ? ch.Size.y : height;

                const GLdouble vertices[24] = {
                    xPos, yPos + h, 0.0, 0.0,
                    xPos, yPos, 0.0, 1.0,
                    xPos + w, yPos, 1.0, 1.0,
                    xPos, yPos + h, 0.0, 0.0,
                    yPos + w, yPos, 1.0, 1.0,
                    xPos + w, yPos + h, 1.0, 0.0
                };

                glBindTexture(GL_TEXTURE_2D, ch.TextureId);

                glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer_->Id());
                glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
                glBindBuffer(GL_ARRAY_BUFFER, 0);

                glDrawArrays(GL_TRIANGLES, 0, 6);

                x += (ch.Advanced >> 6) * scale_;
                colorBuffer_->MoveBuffer(nullptr, 1);
            }
            size_.width = std::fabs(start - x);
            size_.height = height;

        }

        void Text::Unbind() noexcept
        {
            glBindVertexArray(0);
            texture_->Unbind();
            colorBuffer_->MoveBuffer(nullptr, 0);
        }


        void Text::SetFontSize(const unsigned size) noexcept
        {
            fontSize_ = size;
            FT_Set_Pixel_Sizes(fontFace_, fontSize_, fontSize_);
        }

        unsigned Text::GetFontSize() const noexcept
        {
            return fontSize_;
        }

        std::string &Text::GetString() noexcept
        {
            return text_;
        }

        const std::string &Text::GetString() const noexcept
        {
            return text_;
        }

        void Text::SetString(std::string &&text) noexcept
        {
            text_ = std::move(text);
            colorBuffer_->CreateBuffer(text_.size() * 24);
        }

        double Text::GetScale() const noexcept
        {
            return scale_;
        }

        void Text::SetScale(const double scale) noexcept
        {
            scale_ = scale;
        }


        void Text::InitFT() noexcept
        {
            if (FT_Init_FreeType(&ft_))
            {
                APP_LOG("Cannot init FreeType\n");
            }
        }

        unsigned Text::RenderMode() const noexcept
        {
            return GL_DYNAMIC_DRAW;
        }

        int Text::IndexCount() const noexcept
        {
            return static_cast<int>(text_.size());
        }

        int Text::VertexCount() const noexcept
        {
            return IndexCount() * 16;
        }

        unsigned Text::ElementType() const noexcept
        {
            return GL_DOUBLE;
        }

        unsigned Text::IndexElementType() const noexcept
        {
            return GL_UNSIGNED_INT;
        }

        void Text::SetColorFor(const void *)
        {

        }

        void Text::Move(const double x, const double y) noexcept
        {
            pos_.x += x;
            pos_.y += y;
        }

        void Text::SetPos(const double x, const double y) noexcept
        {
            pos_.x = x;
            pos_.y = y;
        }

        Position2D Text::GetPos() const noexcept
        {
            return pos_;
        }

        Size2D Text::Size() const noexcept
        {
            return size_;
        }

        void Text::Resize(Size2D) noexcept
        {

        }

        void Text::StoreBuffers(const void *, size_t, const void *, size_t)
        {

        }

        void Text::LoadTexture(const char *) noexcept
        {

        }

        void Text::StoreTextureBuffer(const void *, size_t) noexcept
        {

        }

        void Text::Rotate(double)
        {

        }

    }
}
