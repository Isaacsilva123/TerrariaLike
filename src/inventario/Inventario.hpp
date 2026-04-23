#pragma once

#include "../utils/Texturas.hpp"
#include "./itens/Iten.hpp"
#include "../interfaces/InterfaceDU.hpp"

class Inventario : public InterfaceDU
{
private:
    Texture2D textura, selected, outroInventario;
    std::unique_ptr<Iten> itens[50];
    int state, dragIndex;
    Vector2 dragPos;

public:
    bool estaAberto;
    Inventario();
    bool isNull();
    bool adicionarItem(Type t);
    Type botarIten();
    void draw();
    void update();
};