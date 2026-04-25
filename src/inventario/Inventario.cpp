#include "./Inventario.hpp"
#include <math.h>

Inventario::Inventario()
{
    textura = Texturas::inventario;
    selected = Texturas::selected;
    outroInventario = Texturas::inventarioSlot;

    estaAberto = false;

    dragIndex = -1;
    dragPos = {0, 0};

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

bool Inventario::adicionarItem(Type t)
{
    for (int i = 0; i < 50; i++)
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

    for (int i = 0; i < 50; i++)
    {
        if (itens[i] == nullptr)
        {
            itens[i] = std::make_unique<Iten>(t);
            return true;
        }
    }
    return false;
}

Type Inventario::botarIten()
{
    if (itens[state] == nullptr)
    {
        return Type::AR;
    }

    itens[state]->quantidade--;
    return itens[state]->tipo;
}

void Inventario::update()
{
    for (int i = 0; i < 50; i++)
    {
        if (itens[i] != nullptr && itens[i]->quantidade <= 0)
        {
            itens[i] = nullptr;
        }
    }

    if (!estaAberto && dragIndex == -1)
    {
        float well = GetMouseWheelMove();
        if (well < 0)
        {
            state = (state + 1) % 10;
        }
        else if (well > 0)
        {
            state = (state - 1 + 10) % 10;
        }
    }

    if (IsKeyPressed(KEY_E))
    {
        dragIndex = -1;
        estaAberto = !estaAberto;
    }

    if (!estaAberto)
    {
        return;
    }

    float widthW = GetScreenWidth();
    float heightW = GetScreenHeight();
    // invX bar
    float hx = (widthW / 2.f) - (textura.width / 2.f);
    // invy bar
    float hy = heightW - textura.height;

    // outro
    float ax = (widthW / 2.f) - (outroInventario.width / 2.f);
    // outro
    float ay = 150;

    Vector2 mousePos = GetMousePosition();
    dragPos = {0, 0};

    if (dragIndex != -1)
    {
        dragPos = mousePos;
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        Rectangle bar = {hx, hy, (float)textura.width, (float)textura.height};
        Rectangle outro = {ax, ay, (float)outroInventario.width, (float)outroInventario.height};
        Rectangle mouseCol = {mousePos.x, mousePos.y, 1, 1};

        if (dragIndex == -1)
        {
            if (CheckCollisionRecs(mouseCol, outro))
            {
                int col = (mousePos.x - outro.x) / 32;
                int row = (mousePos.y - outro.y) / 32;

                for (int i = 10; i < 50; i++)
                {
                    int colI = (i - 10) % 10;
                    int rowI = (i - 10) / 10;

                    if (col == colI && row == rowI)
                    {
                        if (itens[i] != nullptr)
                        {
                            dragIndex = i;
                        }

                        break;
                    }
                }
            }
            else
            {
                if (CheckCollisionRecs(mouseCol, bar))
                {
                    int iten = (mousePos.x - bar.x) / 32;
                    if (itens[iten] != nullptr)
                    {
                        dragIndex = iten;
                    }
                }
            }
        }
        else
        {
            if (CheckCollisionRecs(mouseCol, outro))
            {
                int col = (mousePos.x - outro.x) / 32;
                int row = (mousePos.y - outro.y) / 32;

                for (int i = 10; i < 50; i++)
                {
                    int colI = (i - 10) % 10;
                    int rowI = (i - 10) / 10;

                    if (col == colI && row == rowI)
                    {
                        if (itens[i] == nullptr)
                        {
                            itens[i] = std::move(itens[dragIndex]);
                            itens[dragIndex] = nullptr;
                        }
                        else
                        {
                            if (itens[i]->tipo != itens[dragIndex]->tipo)
                            {
                                std::swap(itens[i], itens[dragIndex]);
                            }
                            else
                            {
                                while (itens[i]->quantidade < 64 && itens[dragIndex]->quantidade > 0)
                                {
                                    itens[i]->quantidade++;
                                    itens[dragIndex]->quantidade--;
                                }
                            }
                        }
                        dragIndex = -1;
                        break;
                    }
                }
            }
            else
            {
                if (CheckCollisionRecs(mouseCol, bar))
                {
                    int iten = (mousePos.x - bar.x) / 32;
                    if (itens[iten] == nullptr)
                    {
                        itens[iten] = std::move(itens[dragIndex]);
                        itens[dragIndex] = nullptr;
                    }
                    else
                    {
                        if (itens[iten]->tipo != itens[dragIndex]->tipo)
                        {
                            std::swap(itens[iten], itens[dragIndex]);
                        }
                        else
                        {
                            while (itens[iten]->quantidade < 64 && itens[dragIndex]->quantidade > 0)
                            {
                                itens[iten]->quantidade++;
                                itens[dragIndex]->quantidade--;
                            }
                        }
                    }
                    dragIndex = -1;
                }
            }
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
    if (!estaAberto)
    {
        DrawTexture(selected, x + (state * 32), y, WHITE);
    }

    // Hotbar
    for (int i = 0; i < 10; i++)
    {
        if (itens[i] != nullptr && i != dragIndex)
        {
            DrawTexturePro(itens[i]->textura, Rectangle{0, 0, 32, 32}, Rectangle{x + (i * 32) + 8, y + 8, 16, 16}, {0, 0}, 0, WHITE);
            const char *t = TextFormat("%i", itens[i]->quantidade);
            float tw = MeasureText(t, 20);
            DrawText(t, x + (i * 32) + 16 - (tw / 2), y + 6, 20, BLACK);
        }
    }

    if (estaAberto)
    {
        float xA = (widthW / 2.f) - (outroInventario.width / 2.f);
        float yA = 150;

        DrawTexture(outroInventario, xA, yA, WHITE);

        // Inventário principal
        for (int i = 10; i < 50; i++)
        {
            if (itens[i] != nullptr && i != dragIndex)
            {
                int col = (i - 10) % 10;
                int row = (i - 10) / 10;
                DrawTexturePro(
                    itens[i]->textura,
                    Rectangle{0, 0, 32, 32},
                    Rectangle{xA + col * 32 + 8, yA + row * 32 + 8, 16, 16},
                    {0, 0}, 0, WHITE);

                const char *t = TextFormat("%i", itens[i]->quantidade);
                float tw = MeasureText(t, 20);
                DrawText(t, xA + col * 32 + 16 - (tw / 2), yA + row * 32 + 8, 20, BLACK);
            }
        }

        // Item flutuando no mouse
        if (dragIndex != -1 && itens[dragIndex] != nullptr)
        {
            DrawTexturePro(
                itens[dragIndex]->textura,
                Rectangle{0, 0, 32, 32},
                Rectangle{dragPos.x - 8, dragPos.y - 8, 16, 16},
                {0, 0}, 0, WHITE);

            const char *t = TextFormat("%i", itens[dragIndex]->quantidade);
            float tw = MeasureText(t, 20);
            DrawText(t, dragPos.x - (tw / 2), dragPos.y - 14, 20, BLACK);
        }
    }
}