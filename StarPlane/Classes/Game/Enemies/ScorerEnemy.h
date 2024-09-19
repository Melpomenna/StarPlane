#pragma once

#include <Core/Actor/Actor.h>

namespace Game
{
    class ScorerEnemy : A_ACTOR
    {
    public:
        ScorerEnemy(Actor *, double, double, double, double, double);

        void Update(double) override;

		void OnEnter(Actor *) override;

    private:
        Actor *playerInstance_;
        double speed_;
    };
} // namespace Game
