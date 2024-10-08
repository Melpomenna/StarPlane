#include "Asteroid.h"

#include <GUI/Support.h>

/**
 *Need to disable log and include Windows
 */
#if !defined(NDEBUG)
#define NDEBUG
#endif
#include <random>
#include <Utils/Config.h>

#include <Game/Config.h>

namespace Game
{
    Asteroid::Asteroid(GUI::Position2D pos, GUI::Size2D size, const double speed) :
        speed_(speed)
    {
        SetObject(GUI::CreateRectangle(size.width, size.height));
        object_.SetTexture(TEXTURE_PATH(Enemies/Asteroid.png));
        object_.SetPosition(pos.x, pos.y);
        SetId(ENEMY_METEOR_ID);
        EnableCollision();
        std::random_device rd;
        std::mt19937 mt{rd()};

        const auto value = static_cast<double>(mt() % 60);
        angle_ = value;
    }

    void Asteroid::Update(const double dt)
    {

        object_.Move(-speed_ * dt, -speed_*1.5 * dt*std::fabs(sin(angle_)));
        const auto posY = object_.GetPos().y;

        object_.Rotate(1);

        if (posY + object_.Size().height <= -object_.WorldSize().height)
        {
            Destroy();
        }
    }

    void Asteroid::OnEnter(Actor *actor)
    {
        if (actor->Id() != ENEMY_BIRD_ID)
        {
            actor->Destroy();
        }
    }

} // namespace Game
