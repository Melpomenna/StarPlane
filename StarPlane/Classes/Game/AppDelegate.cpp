#include "AppDelegate.h"

#include <Game/Player.h>

namespace Game
{
    AppDelegate::AppDelegate()
    {
        CreateCore();
    }

    void AppDelegate::Update(double)
    {

    }


    void AppDelegate::CreateCore()
    {

        constexpr double playerWidth = 150;
        constexpr double playerHeight = 150;
        constexpr double playerSpeed = 300;

        Actor *plane = new Player(playerSpeed, playerWidth, playerHeight);
    }


}
