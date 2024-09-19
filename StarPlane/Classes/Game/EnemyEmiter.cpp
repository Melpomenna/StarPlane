#include "EnemyEmiter.h"

#include <Game/Player.h>
#include <GUI/Support.h>
#include <Game/Enemies/BirdEnemy.h>
#include <Game/Enemies/FightJetEnemy.h>
#include <Game/Enemies/ScorerEnemy.h>
#include <random>

namespace Game
{
    EnemyEmiter::EnemyEmiter(Player *instance, const double width, const double height, const double x,
                             const double y) :
        time_(0), instance_(instance)
    {
        SetObject(GUI::CreateRectangle(width, height));
        object_.SetPosition(x, y);
        object_.FillColor(0, 0, 0, 0);
    }

    void EnemyEmiter::Update(const double dt)
    {
        time_ += dt;
        if (time_ >= delayToCreateEnemy)
        {
            CreateEntity();
            time_ = 0;
        }
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
            constexpr double speed = 100;

            const auto posX = object_.GetPos().x + mt() % static_cast<int>(object_.Size().width);
            const auto posY = object_.GetPos().y - mt() % static_cast<int>(object_.Size().height);
            Actor *enemy = new BirdEnemy(instance_, sizeX, sizeY, posX, posY, speed);
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

            Actor *enemy = new ScorerEnemy(instance_, sizeX, sizeY, posX, posY, speed);
            enemy->Object().Rotate(-90);
        }
        break;
        case EnemyTypes::FighterJet:
        {
            const double speed = instance_->Speed() + std::fmod(mt(), instance_->Speed());
            const auto posX = object_.GetPos().x + mt() % static_cast<int>(object_.Size().width);
            Actor *enemy = new FightJetEnemy(instance_, posX, speed);
            enemy->Object().Rotate(-90);
        }
        break;
        default:
            break;
        }
    }


}
