/**
 *Need to disable log and include Windows
 */
#if !defined(NDEBUG)
#define NDEBUG
#endif
#include <Utils/Config.h>

#include "AppDelegate.h"

#include <Game/Player.h>
#include <Game/EnemyEmiter.h>
#include <Game/Config.h>

#include <GUI/Support.h>
#include <GUI/Render.h>
#include <GUI/Primitives/Text.h>

#include <Core/Actor/ActorSystem.h>

namespace Game
{
    AppDelegate::AppDelegate()
    {
        CreateCore();
    }

    void AppDelegate::Update(double)
    {
        if (!Core::ActorSystem::ResolveActorSystem()->FindById(PLAYER_ID) && emitter_)
        {
            GUI::Node *text = GUI::CreateText(FONT_PATH(Silver.ttf), "You're dead!", 4);
            text->SetPos(0, GUI::Render::ResolveRender()->GetHeight() * 0.5);
            text->FillColor("#00A287");
            text->SetName("LooseLabel");
            emitter_->Destroy();
            emitter_ = nullptr;
        }
    }


    void AppDelegate::CreateCore()
    {

        constexpr double playerWidth = 150;
        constexpr double playerHeight = 150;
        constexpr double playerSpeed = 300;

		auto worldSize = GUI::Size2D{GUI::Render::ResolveRender()->GetWidth(), GUI::Render::ResolveRender()->GetHeight()};

        Player *plane = new Player(playerSpeed, playerWidth, playerHeight);

        const auto worldWidth = worldSize.width;
        const auto worldHeight = worldSize.height;

        GUI::Node *text = GUI::CreateText(FONT_PATH(Silver.ttf), "Score:0", 48);
        text->SetPos(0, worldHeight * 0.9);
        text->FillColor("#00A287");
        text->SetName("ScoreLabel");

        GUI::Render::ResolveRender()->MoveToBack(text);

        GUI::Node *bg = GUI::CreateRectangle(worldWidth * 2, worldHeight * 2);
        bg->SetPos(-worldWidth, worldHeight);
        bg->LoadTexture(TEXTURE_PATH(SpaceBg.png));
        GUI::Render::ResolveRender()->MoveToBack(bg);

        constexpr double enemyEmitterWidth = 50;
        const double enemyEmitterHeight = plane->Object().WorldSize().height - 100;

        Actor *emitter = new EnemyEmiter(enemyEmitterWidth, enemyEmitterHeight,
                                               plane->Object().WorldSize().width - enemyEmitterWidth,
                                               enemyEmitterHeight - 100);
        emitter_ = emitter;
    }


}
