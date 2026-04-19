#include "./Iten.hpp"

Iten::Iten(ItenType t) : tipo(t)
{
    switch (t)
    {
    case ItenType::TERRA:
        textura = Texturas::terra;
        break;
    case ItenType::GRAMA:
        textura = Texturas::grama;
        break;
    case ItenType::PEDRA:
        textura = Texturas::pedra;
        break;
    }
    life = 500;
    quantidade = 1;
};