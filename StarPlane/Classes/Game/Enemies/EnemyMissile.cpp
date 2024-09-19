#include "EnemyMissile.h"

#include <GUI/Support.h>

#if !defined(NDEBUG)
#define NDEBUG
#endif
#include <Utils/Config.h>

#include <Game/Config.h>

#include "GUI/Primitives/Rectangle.h"

namespace Game
{
    EnemyMissile::EnemyMissile(Actor *instance, const double speed, const double width, const double height) :
        playerInstance_(instance), speed_(speed)
    {
        SetObject(GUI::CreateRectangle(width, height));
        object_.SetTexture(TEXTURE_PATH(Enemies/Missle.png));
        SetId(ENEMY_FIGHTJET_MISSLE_ID);
        object_.Rotate(-90);
        EnableCollision();
    }

    void EnemyMissile::Update(const double dt)
    {
        const auto pos = object_.GetPos();
        const auto worldSize = object_.WorldSize();

        const auto nextPosX = speed_ * dt + pos.x;

        if (std::fabs(nextPosX) - object_.Size().width >= worldSize.width)
        {
            Destroy();
            return;
        }

        object_.Move(speed_ * dt, 0);
    }


}
