#pragma once
#include "../interfaces/InterfaceDU.hpp"
#include "../world/World.hpp"

class GameScene : public InterfaceDU
{
private:
    Camera2D camera;
    std::unique_ptr<World> world;

public:
    GameScene();
    
    void draw();
    void update();
};
