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

#include <Game/Config.h>

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
        SetId(PLAYER_MISSLE_ID);
        EnableCollision();
    }


    void Missile::Update(const double dt)
    {
        const auto pos = object_.GetPos();
        const auto worldSize = object_.WorldSize();

        time_ += dt;

        if (time_ >= timeToNextFrame_ && textureIdx_ != 6)
        {
            object_.Resize(object_.Size() + 20);
            time_ = 0;
            std::string textureName = ROOT_TEXTURE_PATH_AS_STR + std::string("Missles/Missle") + std::to_string(
                    textureIdx_) +
                ".png";
            object_.SetTexture(textureName.c_str());
            textureIdx_++;
        }

        const auto nextPosX = speed_ * dt + pos.x;

        if (std::fabs(nextPosX) - object_.Size().width >= worldSize.width)
        {
            Destroy();
            return;
        }

        object_.Move(speed_ * dt, 0);
    }

}
