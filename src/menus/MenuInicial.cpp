#include "MenuInicial.hpp"
#include "../includes/raygui.h"
#include "../utils/gameState/GameState.hpp"

MenuInicial::MenuInicial()
{
    float width = 200;
    float height = 50;
    float x = (GetScreenWidth() / 2.f) - (width / 2.f);
    float y = (GetScreenHeight() / 2.f) - (height / 2.f);

    bounds = {x, y, width, height};
}

void MenuInicial::draw()
{
    if (GuiButton(bounds, "Play"))
    {
        GameState::stt = STATE::GAME;
    }
}