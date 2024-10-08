#pragma once

#include <Core/Actor/Actor.h>

namespace Game
{
    class ScorerEnemy : A_ACTOR
    {
    public:
        ScorerEnemy(double, double, double, double, double);

        void Update(double) override;

        void OnEnter(Actor *) override;

    private:
        double speed_;
    };
} // namespace Game
