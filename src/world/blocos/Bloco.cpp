#include "./Bloco.hpp"

Bloco::Bloco(BlockType b) : tipo(b)
{
    desenhavel = true;

    switch (tipo)
    {
    case BlockType::AR:
        desenhavel = false;
        break;

    case BlockType::TERRA:
        textura = Texturas::terra;
        rigidez = .5f;
        break;

    case BlockType::GRAMA:
        textura = Texturas::grama;
        rigidez = 2.f;
        break;

    case BlockType::PEDRA:
        textura = Texturas::pedra;
        rigidez = 2.5f;
        break;
    }
};