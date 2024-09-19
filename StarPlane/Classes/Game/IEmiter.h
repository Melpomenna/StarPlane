#pragma once

namespace Game
{
    class IEmiter
    {
    public:
        IEmiter() = default;
        virtual ~IEmiter() = default;

        virtual void CreateEntity() noexcept = 0;
    };
}
