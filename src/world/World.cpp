#include "./World.hpp"
#include "../utils/data/Bd.hpp"
#include <math.h>
#include <cstdlib>
#include <ctime>

World::World(Camera2D &c) : c(c)
{
    seed = -1;
    srand(time(0));
}

void World::generate(Vector2 RT, Vector2 LB, int seed)
{
    for (int x = RT.x; x <= LB.x; x++)
    {
        int surface = (WORLD_SIZE / 2) + (10 * sinf(x * 0.051f + seed)) + ((5 * sinf(x * 0.151f + seed)));

        for (int y = RT.y; y <= LB.y; y++)
        {
            if (blocos[y][x] != nullptr)
            {
                continue;
            }

            std::unique_ptr<Bloco> b;

            if (y == surface)
            {
                b = std::make_unique<Bloco>(Type::GRAMA);
                if ((x * 7 + seed * 13) % 50 == 0)
                {
                    int t = 0;
                    if ((x * 7 + seed * 13) % 3)
                    {
                        t = 9;
                    }
                    else if ((x * 7 + seed * 13) % 7)
                    {
                        t = 20;
                    }

                    generateThrees({(float)x, (float)y}, t);
                }
            }
            else if (y > surface + 7)
            {
                b = std::make_unique<Bloco>(Type::PEDRA);
            }
            else if (y > surface)
            {
                b = std::make_unique<Bloco>(Type::TERRA);
            }
            else
            {
                b = std::make_unique<Bloco>(Type::AR);
            }
            blocos[y][x] = std::move(b);
        }
    }
}

void World::generateThrees(Vector2 initial_point, int tamanho)
{
    for (size_t i = 0; i < tamanho; i++)
    {
        if (initial_point.y - 1 - i > 0)
        {
            blocos[(int)initial_point.y - 1 - i][(int)initial_point.x] = std::make_unique<Bloco>(Type::TRONCO);
        }
    }
    if (initial_point.y - (tamanho + 1) > 0)
    {
        blocos[(int)initial_point.y - (tamanho + 1)][(int)initial_point.x] = std::make_unique<Bloco>(Type::FOLHA);

        if (initial_point.y - (tamanho + 2) > 0)
        {
            blocos[(int)initial_point.y - (tamanho + 2)][(int)initial_point.x] = std::make_unique<Bloco>(Type::FOLHA);
        }

        if (initial_point.x - 1 > 0)
        {
            blocos[(int)initial_point.y - (tamanho + 1)][(int)initial_point.x - 1] = std::make_unique<Bloco>(Type::FOLHA);
        }
        if (initial_point.x + 1 < WORLD_SIZE)
        {
            blocos[(int)initial_point.y - (tamanho + 1)][(int)initial_point.x + 1] = std::make_unique<Bloco>(Type::FOLHA);
        }
    }
}

void World::update()
{
    if (!Bd::leu)
    {

        seed = Bd::seed;
        for (auto &b : Bd::blocks)
        {
            blocos[(int)b.y][(int)b.x] = std::make_unique<Bloco>(b.t);
        }
        Bd::leu = true;
    }

    float dt = GetFrameTime();
    posMap1 = {0, 0};
    posMap1 = GetScreenToWorld2D(posMap1, c);
    posMap1 = {posMap1.x / BLOCK_SIZE, posMap1.y / BLOCK_SIZE};

    posMap2 = {(float)GetScreenWidth(), (float)GetScreenHeight()};
    posMap2 = GetScreenToWorld2D(posMap2, c);
    posMap2 = {posMap2.x / BLOCK_SIZE, posMap2.y / BLOCK_SIZE};

    if (posMap1.x < 0)
    {
        posMap1.x = 0;
    }
    if (posMap1.x >= WORLD_SIZE)
    {
        posMap1.x = WORLD_SIZE - 1;
    }
    if (posMap1.y < 0)
    {
        posMap1.y = 0;
    }
    if (posMap1.y >= WORLD_SIZE)
    {
        posMap1.y = WORLD_SIZE - 1;
    }

    if (posMap2.x < 0)
    {
        posMap2.x = 0;
    }
    if (posMap2.x >= WORLD_SIZE)
    {
        posMap2.x = WORLD_SIZE - 1;
    }
    if (posMap2.y < 0)
    {
        posMap2.y = 0;
    }
    if (posMap2.y >= WORLD_SIZE)
    {
        posMap2.y = WORLD_SIZE - 1;
    }

    generate(posMap1, posMap2, seed);

    if (seed != -1 && player == nullptr)
    {
        int spawnX = WORLD_SIZE / 2;

        int surface = (WORLD_SIZE / 2) + (10 * sinf(spawnX * 0.051f + seed)) + (5 * sinf(spawnX * 0.151f + seed));

        player = std::make_unique<Player>(Vector2{(float)spawnX * BLOCK_SIZE, (float)surface * BLOCK_SIZE - 560});
    }

    player->update(posMap1, posMap2, blocos, c, itens);
    c.target = player->pos;

    for (const auto &item : itens)
    {
        item->life -= dt;

        float tileX = item->pos.x / BLOCK_SIZE;
        float tileY = item->pos.y / BLOCK_SIZE;

        bool foraDoMapaX = tileX < posMap1.x || tileX > posMap2.x;
        bool foraDoMapaY = tileY < posMap1.y || tileY > posMap2.y;

        if (foraDoMapaX || foraDoMapaY)
        {
            continue;
        }

        int blockX = (int)tileX;
        int blockYStart = (int)tileY;

        bool colidiu = false;

        for (int y = blockYStart; y <= (int)posMap2.y; y++)
        {
            std::unique_ptr<Bloco> &bloco = blocos[y][blockX];

            if (!bloco || !bloco->desenhavel)
            {
                continue;
            }

            Rectangle areaBloco = {(float)blockX * BLOCK_SIZE, (float)y * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE};
            Rectangle areaItem = {item->pos.x, item->pos.y, 16, 16};

            if (bloco->comColisão && CheckCollisionRecs(areaBloco, areaItem))
            {
                item->pos.y--;
                colidiu = true;
                break;
            }
        }

        if (!colidiu)
        {
            item->pos.y += 30 * dt;
        }
    }
}

void World::draw()
{
    for (int x = posMap1.x; x <= posMap2.x; x++)
    {
        for (int y = posMap1.y; y <= posMap2.y; y++)
        {
            if (blocos[y][x] == nullptr)
            {
                continue;
            }

            if (blocos[y][x]->desenhavel)
            {
                DrawTexture(blocos[y][x]->textura, x * BLOCK_SIZE, y * BLOCK_SIZE, WHITE);
            }
        }
    }

    for (const auto &i : itens)
    {
        DrawTexturePro(i->textura, {0, 0, 32, 32}, {i->pos.x, i->pos.y, 16, 16}, {0, 0}, 0, WHITE);
    }
    player->draw();
}

void World::beginDraw()
{
    player->beginDraw();
}