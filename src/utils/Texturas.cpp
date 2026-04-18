#include "./Texturas.hpp"

Texture2D Texturas::terra{};
Texture2D Texturas::player{};
Texture2D Texturas::grama{};
Texture2D Texturas::pedra{};
Texture2D Texturas::inventario{};
Texture2D Texturas::selected{};

void Texturas::LoadALL(){
    terra = LoadTexture("./src/textures/terra.png");
    player = LoadTexture("./src/textures/Player.png");
    grama = LoadTexture("./src/textures/grama.png");
    pedra = LoadTexture("./src/textures/pedra.png");
    inventario = LoadTexture("./src/textures/inventario.png");
    selected = LoadTexture("./src/textures/inventarioSelected.png");
}

void Texturas::UnloadALL(){
    UnloadTexture(terra);
    UnloadTexture(player);
    UnloadTexture(pedra);
    UnloadTexture(inventario);
    UnloadTexture(selected);
}