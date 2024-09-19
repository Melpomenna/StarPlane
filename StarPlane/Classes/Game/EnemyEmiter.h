#pragma once

#include <Game/IEmiter.h>
#include <Core/Actor/Actor.h>

namespace Game
{

    enum class EnemyTypes
    {
        Bird,
        Scorer,
        FighterJet,
        Non
    };

    class Player;


    class EnemyEmiter : A_ACTOR, public IEmiter
    {
    public:
        EnemyEmiter(Player *, double, double, double, double);

        void Update(double) override;

        void CreateEntity() noexcept override;

    private:
        static constexpr double delayToCreateEnemy = 1.5;
        double time_;
        Player *instance_;
    };

} // namespace Game
