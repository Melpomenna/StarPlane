#pragma once

#include <Core/Actor/Actor.h>

namespace Game
{

    class BirdEnemy : A_ACTOR
    {
    public:
        BirdEnemy(Actor*,double, double, double, double, double);

		void Update(double) override;
    private:
        Actor *playerInstance_;
        double speed_;
        double time_;

    };
} // namespace Game
