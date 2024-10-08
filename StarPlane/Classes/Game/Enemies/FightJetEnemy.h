#pragma once

#include <Core/Actor/Actor.h>

namespace Game
{

    class FightJetEnemy : A_ACTOR
    {
    public:
        FightJetEnemy(Actor *, double, double);

        void Update(double) override;

		void OnEnter(Actor *) override;

    private:
        static constexpr double timeToAttack_ = 1;
        static constexpr double delayToAttack_ = 2;
        static constexpr unsigned maxAttackCount = 5;
        double direction_;
        double speed_;
        double time_, attackTimeout_;
        unsigned attacksCounter_;

    };

} // namespace Game
