#pragma once

#include <Core/Actor/Actor.h>

namespace Game
{

    class Missile : A_ACTOR
    {
    public:
        Missile(double, double, double, double, double);
        ~Missile() override = default;


        void Update(double) override;

    private:
        static constexpr double timeToNextFrame_ = 0.5;
        int textureIdx_;
        double speed_;
        double time_;
    };

} // namespace Game
