#include <iostream>
#include "./game/Game.hpp"

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

    Texturas::UnloadALL();

    CloseWindow();

    return EXIT_SUCCESS;
}