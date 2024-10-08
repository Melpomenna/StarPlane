#pragma once

#include <Core/Actor/Actor.h>

namespace Game
{

	namespace Core
	{
        class Actor;
	}

    class AppDelegate final : A_ACTOR
    {
    public:
        AppDelegate();
        ~AppDelegate() override = default;

        void Update(double) override;

    private:
        void CreateCore();
    private:
        Actor *emitter_;
    };

} // namespace Game
