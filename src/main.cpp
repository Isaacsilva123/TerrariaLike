#include <iostream>
#include "./game/Game.hpp"
#include "./utils/data/Bd.hpp"

#define RAYGUI_IMPLEMENTATION
#include "includes/raygui.h"

int main()
{

    InitWindow(800, 600, "TerrariaLike");

    Texturas::LoadALL();
    std::unique_ptr<Game> game = std::make_unique<Game>();

    while (!WindowShouldClose())
    {
        game->update();
        game->draw();
    }

    if (Bd::leu)
    {
        Bd::save();
    }

    Texturas::UnloadALL();

    CloseWindow();

    return EXIT_SUCCESS;
}