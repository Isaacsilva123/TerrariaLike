#include "Game.hpp"

Game::Game()
{
    GS = std::make_unique<GameScene>();
}

void Game::update()
{
    GS->update();
}

void Game::draw()
{
    GS->draw();
}