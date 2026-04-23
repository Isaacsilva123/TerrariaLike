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

    if (IsKeyDown(KEY_A) && !inventario->estaAberto)
    {
        newPos.x -= velx * dt;
    }

    if (IsKeyDown(KEY_D) && !inventario->estaAberto)
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

    if (onGround && IsKeyDown(KEY_SPACE) && !inventario->estaAberto)
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

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && !inventario->estaAberto)
    {
        Vector2 mouseWorld = GetScreenToWorld2D(GetMousePosition(), c);
        Vector2 mouseBlock = {mouseWorld.x / BLOCK_SIZE, mouseWorld.y / BLOCK_SIZE};

        if (BL[(int)mouseBlock.y][(int)mouseBlock.x] != nullptr && mouseBlock.x >= 0 && mouseBlock.x < WORLD_SIZE && mouseBlock.y >= 0 && mouseBlock.y < WORLD_SIZE - 1 && BL[(int)mouseBlock.y][(int)mouseBlock.x]->desenhavel)
        {
            BL[(int)mouseBlock.y][(int)mouseBlock.x]->rigidez -= force * dt;
            if (BL[(int)mouseBlock.y][(int)mouseBlock.x]->rigidez < 0)
            {
                if (ITS.size() <= 40)
                {
                    Type tipo = BL[(int)mouseBlock.y][(int)mouseBlock.x]->tipo;

                    std::unique_ptr<Iten> iten = std::make_unique<Iten>(tipo);
                    iten->pos = {(float)((int)mouseBlock.x * BLOCK_SIZE + 8), (float)((int)mouseBlock.y * BLOCK_SIZE + 8)};
                    ITS.push_back(std::move(iten));
                }

                BL[(int)mouseBlock.y][(int)mouseBlock.x]->desenhavel = false;
                BL[(int)mouseBlock.y][(int)mouseBlock.x]->tipo = Type::AR;
                BL[(int)mouseBlock.y][(int)mouseBlock.x]->textura = {};
                BL[(int)mouseBlock.y][(int)mouseBlock.x]->rigidez = 0;
            }
        }
    }

    if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT) && !inventario->estaAberto)
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
                    Type t = inventario->botarIten();

                    BL[(int)mouseBlock.y][(int)mouseBlock.x] = std::make_unique<Bloco>(t);
                    BL[(int)mouseBlock.y][(int)mouseBlock.x]->comColisão = true;
                }
            }
        }
    }

    if (IsKeyPressed(KEY_Q)  && !inventario->estaAberto)
    {
        Type t = inventario->botarIten();
        if (t != Type::AR)
        {
            std::unique_ptr<Iten> i = std::make_unique<Iten>(t);

            Vector2 mouseWorld = GetScreenToWorld2D(GetMousePosition(), c);

            if (mouseWorld.x > pos.x)
            {
                i->pos = pos;
                i->pos.x += 100;
            }
            else
            {
                i->pos = pos;
                i->pos.x -= 100;
            }
            if (i->pos.x < 0)
            {
                i->pos.x = 0;
            }
            if (i->pos.x >= (WORLD_SIZE - 1) * BLOCK_SIZE)
            {
                i->pos.x = (WORLD_SIZE - 1) * BLOCK_SIZE - 30;
            }

            ITS.push_back(std::move(i));
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

            if (BL[y][x]->desenhavel && BL[y][x]->comColisão && CheckCollisionRecs({(float)x * BLOCK_SIZE, (float)y * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE}, {pos.x + 2, pos.y, 28, 63}))
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