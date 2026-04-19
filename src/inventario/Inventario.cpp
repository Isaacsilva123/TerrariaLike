#include "./Inventario.hpp"

Inventario::Inventario()
{
    textura = Texturas::inventario;
    selected = Texturas::selected;
    state = 0;
}

bool Inventario::isNull()
{
    if (itens[state] == nullptr)
    {
        return true;
    }
    return false;
}

bool Inventario::adicionarItem(ItenType t)
{
    for (int i = 0; i < 10; i++)
    {
        if (itens[i] == nullptr)
        {
            continue;
        }
        if (itens[i]->tipo == t && itens[i]->quantidade < 64)
        {
            itens[i]->quantidade++;
            return true;
        }
    }

    for (int i = 0; i < 10; i++)
    {
        if (itens[i] == nullptr)
        {
            itens[i] = std::make_unique<Iten>(t);
            return true;
        }
    }
    return false;
}

ItenType Inventario::botarIten()
{
    if (itens[state] == nullptr)
    {
        return ItenType::NULLA;
    }

    itens[state]->quantidade--;
    return itens[state]->tipo;
}

void Inventario::update()
{

    for (int i = 0; i < 10; i++)
    {
        if (itens[i] != nullptr && itens[i]->quantidade <= 0)
        {
            itens[i] = nullptr;
        }
    }

    float well = GetMouseWheelMove();
    if (well < 0)
    {
        state += 1;
        if (state > 9)
        {
            state = 0;
        }
    }
    else if (well > 0)
    {
        state -= 1;
        if (state < 0)
        {
            state = 9;
        }
    }
}

void Inventario::draw()
{
    float widthW = GetScreenWidth();
    float heightW = GetScreenHeight();

    float width = textura.width;
    float height = textura.height;

    float x = (widthW / 2.f) - (width / 2.f);
    float y = heightW - height;

    DrawTexture(textura, x, y, WHITE);
    DrawTexture(selected, x + (state * 32), y, WHITE);

    for (int i = 0; i < 10; i++)
    {
        if (itens[i] != nullptr)
        {
            DrawTexturePro(itens[i]->textura, Rectangle{0, 0, 32, 32}, Rectangle{x + (i * 32) + 8, y + 8, 16, 16}, {0, 0}, 0, WHITE);
            const char *t = TextFormat("%i", itens[i]->quantidade);
            float width = MeasureText(t, 20);
            DrawText(t, x + (i * 32) + (32 / 2) - (width / 2), y + 6, 20, BLACK);
        }
    }
}