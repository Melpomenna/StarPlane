#include "FightJetEnemy.h"

#include <GUI/Support.h>

/**
 *Need to disable log and include Windows
 */
#if !defined(NDEBUG)
#define NDEBUG
#endif
#include <Utils/Config.h>

#include <Game/Config.h>

#include <Game/Enemies/EnemyMissile.h>

#include <Core/Actor/ActorSystem.h>

namespace Game
{
    FightJetEnemy::FightJetEnemy(Actor *player, const double x, const double speed) :
        direction_(0), speed_(speed), time_(0), attackTimeout_(0), attacksCounter_(0)
    {
        const auto size = player->Object().Size();
        SetObject(GUI::CreateRectangle(size.width, size.height));
        object_.SetTexture(TEXTURE_PATH(Enemies/FighterJet.png));
        object_.SetPosition(x, player->Object().GetPos().y);
        SetId(ENEMY_FIGHTJET_ID);
        EnableCollision();
    }

    void FightJetEnemy::Update(const double dt)
    {
        object_.Move(-speed_ * dt, speed_ * dt * direction_);
        const auto posX = object_.GetPos().x;

        time_ += dt;

        if (posX + object_.Size().width <= -object_.WorldSize().width)
        {
            Destroy();
            return;
        }

        if (attacksCounter_ >= maxAttackCount)
        {
            attackTimeout_ += dt;
            if (attackTimeout_ >= delayToAttack_)
            {
                attacksCounter_ = 0;
            }
        }

        Actor *player = Core::ActorSystem::ResolveActorSystem()->FindById(PLAYER_ID);
        if (!player)
        {
            return;
        }


        if ((time_ >= timeToAttack_ || std::fabs(player->Object().GetPos().y - object_.GetPos().y) <= 1E-5) &&
            (attacksCounter_ < maxAttackCount))
        {
            constexpr double speed = -750;
            constexpr double width = 50;
            constexpr double height = 50;

            Actor *missle = new EnemyMissile(player, speed, width, height);
            missle->Object().SetPosition(object_.GetPos().x, object_.GetPos().y - object_.Size().height / 2 + 15);
            time_ = 0;
            attacksCounter_++;
            attackTimeout_ = 0;
        }
    }

    void FightJetEnemy::OnEnter(Actor *actor)
    {
        if (actor->Id() == PLAYER_MISSLE_ID)
        {
            Destroy();
            actor->Destroy();
        }
    }


} // namespace Game
