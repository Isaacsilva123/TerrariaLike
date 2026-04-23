#include "./Texturas.hpp"

Texture2D Texturas::terra{};
Texture2D Texturas::player{};
Texture2D Texturas::grama{};
Texture2D Texturas::pedra{};
Texture2D Texturas::inventario{};
Texture2D Texturas::selected{};
Texture2D Texturas::tronco{};
Texture2D Texturas::folha{};
Texture2D Texturas::tabua{};
Texture2D Texturas::inventarioSlot{};

void Texturas::LoadALL(){
    terra = LoadTexture("./src/textures/terra.png");
    player = LoadTexture("./src/textures/Player.png");
    grama = LoadTexture("./src/textures/grama.png");
    pedra = LoadTexture("./src/textures/pedra.png");
    inventario = LoadTexture("./src/textures/inventario.png");
    selected = LoadTexture("./src/textures/inventarioSelected.png");
    tronco = LoadTexture("./src/textures/troncoDeMadeira.png");
    folha = LoadTexture("./src/textures/folha.png");
    tabua = LoadTexture("./src/textures/tabuasDeMadeira.png");
    inventarioSlot = LoadTexture("./src/textures/inventarioSlot.png");
}

void Texturas::UnloadALL(){
    UnloadTexture(terra);
    UnloadTexture(player);
    UnloadTexture(pedra);
    UnloadTexture(inventario);
    UnloadTexture(selected);
    UnloadTexture(tronco);
    UnloadTexture(folha);
    UnloadTexture(tabua);
    UnloadTexture(inventarioSlot);
}