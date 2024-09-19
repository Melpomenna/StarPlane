#pragma once

#include <Core/Actor/Actor.h>

namespace Game
{

    class AppDelegate final : A_ACTOR
    {
    public:
        AppDelegate();
        ~AppDelegate() override;

        void Update(double) override;

    private:
        void CreateCore();
    };

} // namespace Game
