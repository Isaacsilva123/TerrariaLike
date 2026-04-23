#include "./Bloco.hpp"

Bloco::Bloco(Type b) : tipo(b)
{
    desenhavel = true;
    comColisão = true;

    switch (tipo)
    {
    case Type::AR:
        desenhavel = false;
        break;

    case Type::TERRA:
        textura = Texturas::terra;
        rigidez = .5f;
        break;

    case Type::GRAMA:
        textura = Texturas::grama;
        rigidez = 2.f;
        break;

    case Type::PEDRA:
        textura = Texturas::pedra;
        rigidez = 2.5f;
        break;

        
    case Type::TRONCO:
        textura = Texturas::tronco;
        rigidez = 4.f;
        comColisão = false;
        break;

        
    case Type::TABUA:
        textura = Texturas::tabua;
        rigidez = 2.5f;
        break;
        
    case Type::FOLHA:
        textura = Texturas::folha;
        rigidez = .5f;
        break;
    }
};