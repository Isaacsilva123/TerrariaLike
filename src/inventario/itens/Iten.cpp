#include "./Iten.hpp"

Iten::Iten(Type t) : tipo(t)
{
    switch (t)
    {
    case Type::TERRA:
        textura = Texturas::terra;
        break;
    case Type::GRAMA:
        textura = Texturas::grama;
        break;
    case Type::PEDRA:
        textura = Texturas::pedra;
        break;
    case Type::TRONCO:
        textura = Texturas::tronco;
        break;
    case Type::TABUA:
        textura = Texturas::tabua;
        break;
    case Type::FOLHA:
        textura = Texturas::folha;
        break;
    }
    life = 300;
    quantidade = 1;
};