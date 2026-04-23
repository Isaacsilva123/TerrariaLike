#include "./World.hpp"
#include <math.h>
#include <cstdlib>
#include <ctime>

World::World(Camera2D &c) : c(c)
{
    player = std::make_unique<Player>();
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
                    }else if ((x * 7 + seed * 13) % 7)
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

    generate(posMap1, posMap2, 2000);

    player->update(posMap1, posMap2, blocos, c, itens);
    c.target = player->pos;

    for (const auto &i : itens)
    {

        i->life -= dt;

        if (!(i->pos.x / BLOCK_SIZE >= posMap1.x && i->pos.x / BLOCK_SIZE <= posMap2.x))
        {
            continue;
        }

        if (!(i->pos.y / BLOCK_SIZE >= posMap1.y && i->pos.y / BLOCK_SIZE <= posMap2.y))
        {
            continue;
        }

        int blockX = (int)(i->pos.x / BLOCK_SIZE);
        int blockYStart = (int)(i->pos.y / BLOCK_SIZE);

        if (blockX >= posMap1.x && blockX <= posMap2.x)
        {
            for (int y = blockYStart; y <= posMap2.y; y++)
            {
                if (y < posMap1.y || !blocos[y][blockX]->desenhavel)
                {
                    continue;
                }

                float blockPosX = (float)blockX * BLOCK_SIZE;
                float blockPosY = (float)y * BLOCK_SIZE;

                if (CheckCollisionRecs({blockPosX, blockPosY, BLOCK_SIZE, BLOCK_SIZE}, {i->pos.x, i->pos.y, 16, 16}) && blocos[y][blockX] != nullptr)
                {
                    i->pos.y--;
                }
                else
                {
                    i->pos.y += 30 * dt;
                }
            }
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