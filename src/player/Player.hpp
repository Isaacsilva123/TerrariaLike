#pragma once
#include "../interfaces/InterfaceDU.hpp"
#include "../world/blocos/Bloco.hpp"
#include "../inventario/Inventario.hpp"
#include <vector>

class Player : public InterfaceDU
{
private:
    Texture2D textura;
    bool onGround = false;
    float velx = 200, jumpForce = 600.f, vely = 0, gravity = 1300.f, force = 5.f;

public:
    std::unique_ptr<Inventario> inventario;
    Vector2 pos;
    Player(Vector2 p);
    void update(Vector2 LT, Vector2 RB, std::unique_ptr<Bloco> BL[WORLD_SIZE][WORLD_SIZE], Camera2D &c, std::vector<std::shared_ptr<Iten>> &ITS);
    bool colision(Vector2 LT, Vector2 RB, std::unique_ptr<Bloco> BL[WORLD_SIZE][WORLD_SIZE], Vector2 pos);
    void draw();
    void beginDraw();
};