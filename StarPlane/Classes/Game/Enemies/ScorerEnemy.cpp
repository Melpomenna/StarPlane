#include "ScorerEnemy.h"

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
    ScorerEnemy::ScorerEnemy(const double width, const double height, const double x, const double y,
                             const double speed) :
        speed_(speed)
    {
        SetObject(GUI::CreateRectangle(width, height));
        object_.SetTexture(TEXTURE_PATH(Enemies/Scorer.png));
        object_.SetPosition(x, y);
        SetId(ENEMY_SCORER_ID);
        EnableCollision();
    }

    void ScorerEnemy::Update(const double dt)
    {
        object_.Move(-speed_ * dt, 0);
        const auto posX = object_.GetPos().x;

        if (posX + object_.Size().width <= -object_.WorldSize().width)
        {
            Destroy();
        }
    }

    void ScorerEnemy::OnEnter(Actor *actor)
    {
        if (actor->Id() == PLAYER_MISSLE_ID)
        {
            Destroy();
            actor->Destroy();
        }
    }


} // namespace Game
