#pragma once

#include <Core/Actor/Actor.h>

namespace Game
{
    class Player final : A_ACTOR
    {
    public:
        Player(double, double, double);
        ~Player() override = default;

        void Update(double) override;

        void OnPress(Core::Mouse::Key) override;
        void OnMouseMove(double, double, Core::MouseDirection, Core::MouseDirection) override;
        void OnMouseStopMove() override;
        bool FindBindings(Core::Mouse::Key, const int param) override;

        double Speed() const noexcept;

        void OnEnter(Actor *) override;

        void UpdateScore();

    private:
        bool isMove_;
        double speed_;
        double direction_;
        int score_;
    };

} // namespace Game
