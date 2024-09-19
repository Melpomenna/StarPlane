#include "Player.h"

#include <GUI/Support.h>
#include <Core/Controller/Mouse/MouseEvents.h>

/**
 *Need to disable log and include Windows
 */
#if !defined(NDEBUG)
#define NDEBUG
#endif
#include <Utils/Config.h>

#include <Game/Missile.h>
#include <Game/Config.h>

namespace Game
{
    Player::Player(const double speed, const double width, const double height) :
        isMove_(false), speed_(speed), direction_(1)
    {
        SetObject(GUI::CreateRectangle(width, height));
        object_.SetTexture(TEXTURE_PATH(Plane.png));

        /**
         * setting the player's position 1/3 of the screen vertically
         */
        object_.SetPositionByWindow(-0.3, 0);
        object_.Rotate(90);
        SetId(PLAYER_ID);
        EnableCollision();
    }

    void Player::OnMouseMove(double, double, Core::MouseDirection, Core::MouseDirection directionY)
    {
        if (directionY == Core::MouseDirection::Up)
        {
            direction_ = 1;
        }

        if (directionY == Core::MouseDirection::Down)
        {
            direction_ = -1;
        }

        isMove_ = true;
    }

    void Player::OnPress(Core::Mouse::Key)
    {
        constexpr double speed = 750;
        constexpr double width = 50;
        constexpr double height = 50;
        auto pos = object_.GetPos();
        Actor *missile = new Missile(speed, width, height, pos.x + object_.Size().width, pos.y - height / 2 - 15);
        missile->Object().Rotate(object_.Angle());
    }

    void Player::OnMouseStopMove()
    {
        isMove_ = false;
    }


    void Player::Update(const double dt)
    {
        if (isMove_)
        {
            const auto pos = object_.GetPos();
            const auto worldSize = object_.WorldSize();

            const auto nextPosY = direction_ * speed_ * dt + pos.y;

            const auto nextPosY2 = direction_ * speed_ * dt + pos.y - object_.Size().height;

            const auto check = std::fabs(nextPosY) >= worldSize.height || std::fabs(nextPosY2) >= worldSize.height;

            if (check)
            {
                return;
            }

            object_.Move(0, direction_ * speed_ * dt);
        }
    }

    void Player::OnEnter(Actor *actor)
    {
        if (actor->Id() != PLAYER_MISSLE_ID)
        {

        }
    }


    double Player::Speed() const noexcept
    {
        return speed_;
    }


    bool Player::FindBindings(const Core::Mouse::Key key, const int)
    {
        return key == Core::Mouse::Key::Left;
    }

}
