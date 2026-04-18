#pragma once
#include "./BlockType.hpp"
#include "../../utils/Texturas.hpp"

class Bloco
{
public:
    BlockType tipo;
    Texture2D textura;
    float rigidez;
    bool desenhavel;
    Bloco(BlockType t);
};