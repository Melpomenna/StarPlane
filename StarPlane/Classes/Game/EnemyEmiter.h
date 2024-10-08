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

    class EnemyEmiter : A_ACTOR, public IEmiter
    {
    public:
        EnemyEmiter(double, double, double, double);

        void Update(double) override;

        void CreateEntity() noexcept override;

    private:
        void CreateAsteroid();

    private:
        double delayToCreateEnemy = 1;
        static constexpr double delayToCreateAsteroid = 7.5;
        static constexpr double levelCount = 25;
        static constexpr double delayTimeForNewLevel = 0.015;
        static constexpr double minDeltaTime = 0.25;
        double time_;
        double timeToAsteroid_;
        double currentLevel = 0;
    };

} // namespace Game
