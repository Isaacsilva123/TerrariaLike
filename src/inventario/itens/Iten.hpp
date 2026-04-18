#pragma once
#include "./ItenType.hpp"
#include "../../utils/Texturas.hpp"

class Iten
{
public:
    ItenType tipo;
    Texture2D textura;
    int quantidade;
    Vector2 pos;
    float life;
    Iten(ItenType t);
};