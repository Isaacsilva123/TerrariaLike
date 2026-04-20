#pragma once
#include "../../utils/Type.hpp"
#include "../../utils/Texturas.hpp"

class Iten
{
public:
    Type tipo;
    Texture2D textura;
    int quantidade;
    Vector2 pos;
    float life;
    Iten(Type t);
};