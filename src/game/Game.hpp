#pragma once
#include "../interfaces/InterfaceDU.hpp"
#include "../world/World.hpp"

class Game : public InterfaceDU
{
private:
    Camera2D camera;
    std::unique_ptr<World> world;

public:
    Game();

    void update();
    void draw();
};