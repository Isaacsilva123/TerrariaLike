#include "GameScene.hpp"
#include "../utils/gameState/GameState.hpp"
#include "../utils/data/Bd.hpp"
#include <cmath>
#include <time.h>

GameScene::GameScene()
{
    srand(time(NULL));
    camera = {};
    camera.rotation = 0;
    camera.offset = {GetScreenWidth() / 2.f, GetScreenHeight() / 2.f};
    camera.target = {WORLD_SIZE / 2.f * BLOCK_SIZE, 0};
    camera.zoom = 1.f;
}

void GameScene::update()
{
    if (world == nullptr)
    {
        camera = {};
        camera.rotation = 0;
        camera.offset = {GetScreenWidth() / 2.f, GetScreenHeight() / 2.f};
        camera.target = {WORLD_SIZE / 2.f * BLOCK_SIZE, 0};
        camera.zoom = 1.f;
        world = std::make_unique<World>(camera);
    }

    world->update();
    if (IsKeyDown(KEY_R))
    {
        for (int i = 0; i < 50; i++)
        {
            Bd::itens[i] = world->player->inventario->itens[i];
        }

        Bd::save();

        for (size_t i = 0; i < 50; i++)
        {
            Bd::itens[i] = nullptr;
        }

        Bd::blocks = {};

        Bd::leu = false;
        world = nullptr;
        GameState::stt = STATE::MENUI;
    }
}

void GameScene::draw()
{
    BeginDrawing();
    ClearBackground(GRAY);
    BeginMode2D(camera);
    world->draw();

    EndMode2D();
    world->beginDraw();
    // DrawFPS(10, 10);
    EndDrawing();
}