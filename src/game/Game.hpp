#pragma once
#include "../interfaces/InterfaceDU.hpp"
#include "../scenes/GameScene.hpp"

class Game : public InterfaceDU
{
private:
    std::unique_ptr<GameScene> GS;

public:
    Game();

    void update();
    void draw();
};