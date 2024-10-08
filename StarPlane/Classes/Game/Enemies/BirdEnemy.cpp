#include "BirdEnemy.h"

#include <GUI/Support.h>

/**
 *Need to disable log and include Windows
 */
#if !defined(NDEBUG)
#define NDEBUG
#endif
#include <Utils/Config.h>

#include <Game/Config.h>

namespace Game
{
    BirdEnemy::BirdEnemy(const double width, const double height, const double x, const double y,
                         const double speed) :
        speed_(speed), time_(0)
    {
        SetObject(GUI::CreateRectangle(width, height));
        object_.SetTexture(TEXTURE_PATH(Enemies/Bird.png));
        object_.SetPosition(x, y);
        SetId(ENEMY_BIRD_ID);
        EnableCollision();
    }

    void BirdEnemy::Update(const double dt)
    {
        time_ += dt;
        object_.Move(-speed_ * dt, sin(time_) * speed_ * dt);
        const auto posX = object_.GetPos().x;

        if (posX + object_.Size().width <= -object_.WorldSize().width)
        {
            Destroy();
        }
    }

    void BirdEnemy::OnEnter(Actor *actor)
    {
        if (actor->Id() == PLAYER_MISSLE_ID)
        {
            Destroy();
            actor->Destroy();
        }
    }

}
