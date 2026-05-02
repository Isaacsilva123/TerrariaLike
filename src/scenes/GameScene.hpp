#pragma once
#include "../interfaces/InterfaceDU.hpp"
#include "../world/World.hpp"

class GameScene : public InterfaceDU
{
private:
    Camera2D camera;

public:
    GameScene();

    std::unique_ptr<World> world;
    void draw();
    void update();
};
