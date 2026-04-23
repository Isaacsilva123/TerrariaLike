#include "./Inventario.hpp"

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
    float hx = (widthW / 2.f) - (textura.width / 2.f);
    float hy = heightW - textura.height;
    float ax = (widthW / 2.f) - (outroInventario.width / 2.f);
    float ay = 150;

    Vector2 mousePos = GetMousePosition();

    auto getSlot = [&]() -> int
    {
        for (int i = 0; i < 10; i++)
        {
            Rectangle slot = {hx + i * 32.f, hy, 32, 32};
            if (CheckCollisionPointRec(mousePos, slot))
            {
                return i;
            }
        }
        for (int i = 10; i < 50; i++)
        {
            int col = (i - 10) % 10;
            int row = (i - 10) / 10;
            Rectangle slot = {ax + col * 32.f, ay + row * 32.f, 32, 32};
            if (CheckCollisionPointRec(mousePos, slot))
            {
                return i;
            }
        }
        return -1;
    };

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && dragIndex == -1)
    {
        int slot = getSlot();
        if (slot != -1 && itens[slot] != nullptr)
        {
            dragIndex = slot;
        }
    }

    if (dragIndex != -1)
    {
        dragPos = mousePos;
    }

    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && dragIndex != -1)
    {
        int dest = getSlot();

        if (dest != -1 && dest != dragIndex)
        {
            if (itens[dest] == nullptr)
            {
                itens[dest] = std::move(itens[dragIndex]);
            }
            else if (itens[dest]->tipo == itens[dragIndex]->tipo)
            {
                int transfere = std::min(64 - itens[dest]->quantidade, itens[dragIndex]->quantidade);
                itens[dest]->quantidade += transfere;
                itens[dragIndex]->quantidade -= transfere;
            }
            else
            {
                std::swap(itens[dragIndex], itens[dest]);
            }
        }

        dragIndex = -1;
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