#include <Utils/Config.h>
#include "Rectangle.h"

#include <GL/glew.h>


#include "GUI/Buffer.h"
#include "GUI/Texture.h"

namespace Game
{
    namespace GUI
    {
        Rectangle::Rectangle(const double width, const double height) :
            Node(SHADERS_PATH(BasicVertex.vert), SHADERS_PATH(BasicFrag.frag), GL_DYNAMIC_DRAW)
        {
            width_ = width;
            height_ = height;
            currentPosX_ = 0;
            currentPosY_ = 0;

            const unsigned indexes[] = {
                0, 1, 2,
                2, 3, 0
            };

            const double noBlendColor[] = {
                1, 1, 1, 1,
                1, 1, 1, 1,
                1, 1, 1, 1,
                1, 1, 1, 1
            };

            const double basePos[] = {
                0, 0,
                0, -height_,
                width_, -height_,
                width_, 0
            };

            const double textureCoords[] = {
                1, 0,
                1, 1,
                0, 1,
                0, 0,
            };

            indexBuffer_->MoveBuffer(indexes, 6);
            vertexBuffer_->MoveBuffer(basePos, 8);
            colorBuffer_->MoveBuffer(noBlendColor, 16);
            texture_->StoreBuffer(textureCoords, 8);
        }

        void Rectangle::Resize(const Size2D size) noexcept
        {
            const auto diffSizeX = size.width - width_;
            const auto diffSizeY = size.height - height_;
            height_ = size.height;
            width_ = size.width;

            double *coords = vertexBuffer_->CastToArray<double>();

            coords[3] -= diffSizeY;
            coords[4] += diffSizeX;
            coords[5] -= diffSizeY;
            coords[6] += diffSizeX;

        }

        void Rectangle::StoreBuffers(const void *, const size_t, const void *,
                                     const size_t)
        {

        }

        void Rectangle::SetPos(const double x, const double y) noexcept
        {
            Move(x - currentPosX_, y - currentPosY_);
        }

        void Rectangle::Move(const double x, const double y) noexcept
        {
            double *coords = vertexBuffer_->CastToArray<double>();
            coords[0] += x;
            coords[1] += y;

            coords[2] += x;
            coords[3] += y;

            coords[4] += x;
            coords[5] += y;

            coords[6] += x;
            coords[7] += y;

            currentPosX_ = coords[0];
            currentPosY_ = coords[1];
        }

        Position2D Rectangle::GetPos() const noexcept
        {
            return {currentPosX_, currentPosY_};
        }


        Size2D Rectangle::Size() const noexcept
        {
            return {width_, height_};
        }


    }
}
