#include "Game.hpp"
#include <cmath>
#include <time.h>
Game::Game()
{
    srand(time(NULL));
    camera = {};
    camera.rotation = 0;
    camera.offset = {GetScreenWidth() / 2.f, GetScreenHeight() / 2.f};
    camera.target = {WORLD_SIZE / 2.f * BLOCK_SIZE, 0};
    camera.zoom = 1.f;

    world = std::make_unique<World>(camera);
    // world->generate(rand() % 200000);
}

void Game::update()
{
    world->update();
}

void Game::draw()
{
    BeginDrawing();
    ClearBackground(GRAY);
    BeginMode2D(camera);
    world->draw();

    EndMode2D();
    world->beginDraw();
    DrawFPS(10, 10);
    EndDrawing();
}