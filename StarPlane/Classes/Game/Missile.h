#pragma once

#include <Core/Actor/Actor.h>

namespace Game
{
    class Player;

    class Missile : A_ACTOR
    {
    public:
        Missile(Player *, double, double, double, double, double);
        ~Missile() override = default;


        void Update(double) override;

        void OnEnter(Actor *) override;

    private:
        Player *player_;
        static constexpr double timeToNextFrame_ = 0.25;
        int textureIdx_;
        double speed_;
        double time_;
    };

} // namespace Game
