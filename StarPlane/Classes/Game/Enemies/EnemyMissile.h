#pragma once

#include <Core/Actor/Actor.h>

namespace Game
{
    class EnemyMissile : A_ACTOR
    {
    public:
        EnemyMissile(Actor *, double, double, double);

        void Update(double) override;

    private:
        Actor *playerInstance_;
        double speed_;
    };

} // namespace Game
