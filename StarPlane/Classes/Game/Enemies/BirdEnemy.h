#pragma once

#include <Core/Actor/Actor.h>

namespace Game
{

    class BirdEnemy : A_ACTOR
    {
    public:
        BirdEnemy(double, double, double, double, double);

        void Update(double) override;
        void OnEnter(Actor *) override;

    private:
        double speed_;
        double time_;

    };
} // namespace Game
