#pragma once
#include "./blocos/Bloco.hpp"
#include "../interfaces/InterfaceDU.hpp"
#include "../player/Player.hpp"
#include "../inventario/Inventario.hpp"
#include <vector>

class World : public InterfaceDU
{
private:
    Camera2D &c;
    std::unique_ptr<Player> player;
    std::vector<std::unique_ptr<Iten>> itens;
    Vector2 posMap1;
    Vector2 posMap2;

public:
    World(Camera2D &c);

    std::unique_ptr<Bloco> blocos[WORLD_SIZE][WORLD_SIZE];
    void generate(Vector2 RT, Vector2 LB, int seed);
    void generateThrees(Vector2 initial_point);
    void update();
    void draw();
    void beginDraw();
};
