#pragma once

#include <Core/Actor/Actor.h>

namespace Game
{
    class Asteroid : A_ACTOR
    {
    public:
        Asteroid(GUI::Position2D, GUI::Size2D,double);

        void Update(double) override;

        void OnEnter(Actor *) override;

    private:
        double speed_;
        double angle_;
    };
} // namespace Game
