#pragma once
#include "../../utils/Type.hpp"
#include "../../utils/Texturas.hpp"

class Bloco
{
public:
    Type tipo;
    Texture2D textura;
    float rigidez;
    bool desenhavel;
    Bloco(Type t);
};