#include "Player.hpp"
#include "../utils/Texturas.hpp"
#include <math.h>
#include <algorithm>

Player::Player()
{
    textura = Texturas::player;
    inventario = std::make_unique<Inventario>();
    pos = {0, 0};
}

void Player::update(Vector2 LT, Vector2 RB, std::unique_ptr<Bloco> BL[WORLD_SIZE][WORLD_SIZE], Camera2D &c, std::vector<std::unique_ptr<Iten>> &ITS)
{

    inventario->update();

    Vector2 newPos = pos;
    float dt = GetFrameTime();

    if (IsKeyDown(KEY_A))
    {
        newPos.x -= velx * dt;
    }

    if (IsKeyDown(KEY_D))
    {
        newPos.x += velx * dt;
    }

    if (colision(LT, RB, BL, newPos))
    {
        newPos.x = pos.x;
    }
    else
    {
        pos.x = newPos.x;
    }

    if (onGround && IsKeyDown(KEY_SPACE))
    {
        vely = -jumpForce;
    }

    vely += gravity * dt;
    newPos = {pos.x, pos.y + vely * dt};

    if (colision(LT, RB, BL, newPos))
    {
        newPos.y = pos.y;
        if (vely > 0)
        {
            onGround = true;
        }
        else
        {
            onGround = false;
        }
        vely = 0;
    }
    else
    {
        pos.y = newPos.y;
        onGround = false;
    }

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    {
        Vector2 mouseWorld = GetScreenToWorld2D(GetMousePosition(), c);
        Vector2 mouseBlock = {mouseWorld.x / BLOCK_SIZE, mouseWorld.y / BLOCK_SIZE};

        if (BL[(int)mouseBlock.y][(int)mouseBlock.x] != nullptr && mouseBlock.x >= 0 && mouseBlock.x < WORLD_SIZE && mouseBlock.y >= 0 && mouseBlock.y < WORLD_SIZE - 1 && BL[(int)mouseBlock.y][(int)mouseBlock.x]->desenhavel)
        {
            BL[(int)mouseBlock.y][(int)mouseBlock.x]->rigidez -= force * dt;
            if (BL[(int)mouseBlock.y][(int)mouseBlock.x]->rigidez < 0)
            {
                if (ITS.size() <= 255)
                {
                    ItenType tipo;
                    switch (BL[(int)mouseBlock.y][(int)mouseBlock.x]->tipo)
                    {
                    case BlockType::GRAMA:
                        tipo = ItenType::GRAMA;
                        break;
                    case BlockType::TERRA:
                        tipo = ItenType::TERRA;
                        break;
                    case BlockType::PEDRA:
                        tipo = ItenType::PEDRA;
                        break;
                    }

                    std::unique_ptr<Iten> iten = std::make_unique<Iten>(tipo);
                    iten->pos = {(float)((int)mouseBlock.x * BLOCK_SIZE + 8), (float)((int)mouseBlock.y * BLOCK_SIZE + 8)};
                    ITS.push_back(std::move(iten));
                }

                BL[(int)mouseBlock.y][(int)mouseBlock.x]->desenhavel = false;
                BL[(int)mouseBlock.y][(int)mouseBlock.x]->tipo = BlockType::AR;
                BL[(int)mouseBlock.y][(int)mouseBlock.x]->textura = {};
                BL[(int)mouseBlock.y][(int)mouseBlock.x]->rigidez = 0;
            }
        }
    }

    if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
    {
        Vector2 mouseWorld = GetScreenToWorld2D(GetMousePosition(), c);
        Vector2 mouseBlock = {(float)(int)(mouseWorld.x / BLOCK_SIZE), (float)(int)(mouseWorld.y / BLOCK_SIZE)};
        if (!CheckCollisionRecs({mouseBlock.x * BLOCK_SIZE, mouseBlock.y * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE}, {pos.x, pos.y, 32, 64}))
        {
            Vector2 mouseBlock = {mouseWorld.x / BLOCK_SIZE, mouseWorld.y / BLOCK_SIZE};
            if (BL[(int)mouseBlock.y][(int)mouseBlock.x] != nullptr)
            {
                if (mouseBlock.x >= 0 && mouseBlock.x < WORLD_SIZE && mouseBlock.y >= 0 && mouseBlock.y < WORLD_SIZE && !BL[(int)mouseBlock.y][(int)mouseBlock.x]->desenhavel && !inventario->isNull())
                {
                    ItenType t = inventario->botarIten();

                    BlockType tipo;
                    switch (t)
                    {
                    case ItenType::GRAMA:
                        tipo = BlockType::GRAMA;
                        break;
                    case ItenType::TERRA:
                        tipo = BlockType::TERRA;
                        break;
                    case ItenType::PEDRA:
                        tipo = BlockType::PEDRA;
                        break;
                    }
                    BL[(int)mouseBlock.y][(int)mouseBlock.x] = std::make_unique<Bloco>(tipo);
                }
            }
        }
    }

    ITS.erase(std::remove_if(ITS.begin(), ITS.end(), [&](const auto &item)
                             { if (CheckCollisionRecs({item->pos.x, item->pos.y, 16, 16},{pos.x + (32 / 2) - (100 / 2), pos.y + (64 / 2) - (100 / 2), 100, 100})) {
                                       return inventario->adicionarItem(item->tipo);
                                   } return item->life <= 0; }),
              ITS.end());
}

bool Player::colision(Vector2 LT, Vector2 RB, std::unique_ptr<Bloco> BL[WORLD_SIZE][WORLD_SIZE], Vector2 pos)
{
    if (pos.x < 0 || pos.x / BLOCK_SIZE > WORLD_SIZE - 1 || pos.y < 0 || pos.y / BLOCK_SIZE > WORLD_SIZE - 2)
    {
        return true;
    }

    for (int x = LT.x; x <= RB.x; x++)
    {
        for (int y = LT.y; y <= RB.y; y++)
        {
            if (BL[y][x] == nullptr)
            {
                continue;
            }

            if (BL[y][x]->desenhavel && CheckCollisionRecs({(float)x * BLOCK_SIZE, (float)y * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE}, {pos.x + 2, pos.y, 28, 63}))
            {
                return true;
            }
        }
    }
    return false;
}

void Player::draw()
{
    DrawTexture(textura, pos.x, pos.y, WHITE);
}

void Player::beginDraw()
{
    inventario->draw();
}