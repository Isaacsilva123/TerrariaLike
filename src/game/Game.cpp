#include "Game.hpp"
#include "../utils/gameState/GameState.hpp"

Game::Game()
{
    GS = std::make_unique<GameScene>();
    MIS = std::make_unique<MenuInitialScene>();
}

void Game::update()
{
    if (GameState::stt == STATE::GAME)
    {
        GS->update();
    }else
    {
        MIS->update();
    }
    
}

void Game::draw()
{
    if (GameState::stt == STATE::GAME)
    {
        GS->draw();
    }else
    {
        MIS->draw();
    }
    
}