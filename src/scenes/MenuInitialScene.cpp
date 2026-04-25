#include "MenuInitialScene.hpp"
#include "../includes/raygui.h"

MenuInitialScene::MenuInitialScene()
{
    menuI = std::make_unique<MenuInicial>();
}

void MenuInitialScene::draw()
{
    BeginDrawing();
    ClearBackground(GetColor(GuiGetStyle(DEFAULT,BACKGROUND_COLOR)));
    menuI->draw();
    EndDrawing();
}

void MenuInitialScene::update()
{
}