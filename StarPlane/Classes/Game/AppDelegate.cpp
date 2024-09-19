#include "AppDelegate.h"

#include <Game/Player.h>
#include <Game/EnemyEmiter.h>

namespace Game
{
    AppDelegate::AppDelegate()
    {
        CreateCore();
    }

	AppDelegate::~AppDelegate()
    {
        
    }


    void AppDelegate::Update(double)
    {

    }


    void AppDelegate::CreateCore()
    {

        constexpr double playerWidth = 150;
        constexpr double playerHeight = 150;
        constexpr double playerSpeed = 300;


        Player *plane = new Player(playerSpeed, playerWidth, playerHeight);

        constexpr double enemyEmiterWidth = 50;
        const double enemyEmiterHeight = plane->Object().WorldSize().height-100;

        Actor *emiter = new EnemyEmiter(plane, enemyEmiterWidth, enemyEmiterHeight,
                                        plane->Object().WorldSize().width - enemyEmiterWidth, enemyEmiterHeight-100);
    }


}
