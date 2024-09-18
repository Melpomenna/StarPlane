#include "Missile.h"


#include <GUI/Support.h>

/**
 *Need to disable log and include Windows
 */
#if !defined(NDEBUG)
#define NDEBUG
#endif
#include <string>
#include <Utils/Config.h>

namespace Game
{
    Missile::Missile(const double speed, const double width, const double height, const double posX,
                     const double posY) :
        textureIdx_(2),
        speed_(speed), time_()
    {
        SetObject(GUI::CreateRectangle(width, height));
        object_.SetTexture(TEXTURE_PATH(Missles/Missle1.png));
        object_.SetPosition(posX, posY);
    }


    void Missile::Update(const double dt)
    {
        const auto pos = object_.GetPos();
        const auto worldSize = object_.WorldSize();

        time_ += dt;

        if (time_ >= timeToNextFrame_)
        {
            time_ = 0;
            std::string textureName = ROOT_TEXTURE_PATH_AS_STR + std::string("Missles/Missle") + std::to_string(
                    textureIdx_) +
                ".png";
            object_.SetTexture(textureName.c_str());
            if (textureIdx_ != 5)
            {
                textureIdx_++;
            }
        }

        const auto nextPosY = speed_ * dt + pos.y;

        if (std::fabs(nextPosY) >= worldSize.height)
        {
            Destroy();
            return;
        }

        object_.Move(0, speed_ * dt);
    }

}
