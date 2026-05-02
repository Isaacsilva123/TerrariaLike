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
        for (int i = 0; i < 50; i++)
        {
            Bd::itens[i] = game->GS->world->player->inventario->itens[i];
        }

        Bd::save();
    }

    Texturas::UnloadALL();

    CloseWindow();

    return EXIT_SUCCESS;
}