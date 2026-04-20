#pragma once

#include "../utils/Texturas.hpp"
#include "./itens/Iten.hpp"
#include "../interfaces/InterfaceDU.hpp"

class Inventario : public InterfaceDU
{
private:
    Texture2D textura;
    Texture2D selected;
    std::unique_ptr<Iten> itens[10];
    int state;
public:
    Inventario();
    bool isNull();
    bool adicionarItem(Type t);
    Type botarIten();
    void draw();
    void update();
};