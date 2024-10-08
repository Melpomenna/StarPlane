#include "EnemyEmiter.h"

#include <Game/Config.h>
#include <Core/Actor/ActorSystem.h>
#include <Game/Player.h>
#include <GUI/Support.h>
#include <Game/Enemies/BirdEnemy.h>
#include <Game/Enemies/FightJetEnemy.h>
#include <Game/Enemies/ScorerEnemy.h>
#include <Game/Enemies/Asteroid.h>
#include <random>

namespace Game
{
    EnemyEmiter::EnemyEmiter(const double width, const double height, const double x,
                             const double y) :
        time_(0), timeToAsteroid_(0)
    {
        SetObject(GUI::CreateRectangle(width, height));
        object_.SetPosition(x, y);
        object_.FillColor(0, 0, 0, 0);
    }

    void EnemyEmiter::Update(const double dt)
    {
        time_ += dt;
        timeToAsteroid_ += dt;
        if (time_ >= delayToCreateEnemy)
        {
            CreateEntity();
            time_ = 0;
            ++currentLevel;
            if (currentLevel == levelCount)
            {
                currentLevel = 0;
                delayToCreateEnemy -= delayTimeForNewLevel;
                delayToCreateEnemy = std::min(delayToCreateEnemy, minDeltaTime);
            }
        }

        if (timeToAsteroid_ >= delayToCreateAsteroid)
        {
            CreateAsteroid();
            timeToAsteroid_ = 0;
        }
    }

    void EnemyEmiter::CreateAsteroid()
    {
        const auto pos = object_.GetPos();
        const auto size = object_.Size();

		const auto asteroidPos = GUI::Position2D{pos.x + size.width, pos.y};
        const auto asteroidSize = GUI::Size2D{350, 350};
        const auto speed = 750;
        Actor *asteroid = new Asteroid(asteroidPos, asteroidSize, speed);
        (void)asteroid;
    }


    void EnemyEmiter::CreateEntity() noexcept
    {
        std::random_device rd;
        std::mt19937 mt{rd()};

        const auto value = static_cast<EnemyTypes>(mt() % static_cast<int>(EnemyTypes::Non));


        switch (value)
        {
        case EnemyTypes::Bird:
        {
            constexpr double sizeX = 100;
            constexpr double sizeY = 100;
            constexpr double speed = 200;

            const auto posX = object_.GetPos().x + mt() % static_cast<int>(object_.Size().width);
            const auto posY = -object_.Size().height + mt() % static_cast<int>(object_.Size().height);
            Actor *enemy = new BirdEnemy(sizeX, sizeY, posX, posY, speed);
            enemy->Object().Rotate(-90);
        }
        break;
        case EnemyTypes::Scorer:
        {
            constexpr double sizeX = 200;
            constexpr double sizeY = 200;

            const auto posX = object_.GetPos().x + mt() % static_cast<int>(object_.Size().width);
            const auto posY = object_.GetPos().y - mt() % static_cast<int>(object_.Size().height / 2);

            const double speed = posY > (object_.Size().height - object_.Size().height / 4) ? 500 : 300;

            Actor *enemy = new ScorerEnemy(sizeX, sizeY, posX, posY, speed);
            enemy->Object().Rotate(-90);
        }
        break;
        case EnemyTypes::FighterJet:
        {

            Player *instance = static_cast<Player *>(Core::ActorSystem::ResolveActorSystem()->FindById(PLAYER_ID));
            const double speed = instance->Speed() + std::fmod(mt(), instance->Speed());
            const auto posX = object_.GetPos().x + mt() % static_cast<int>(object_.Size().width);
            Actor *enemy = new FightJetEnemy(instance, posX, speed);
            enemy->Object().Rotate(-90);
        }
        break;
        default:
            break;
        }
    }


}
