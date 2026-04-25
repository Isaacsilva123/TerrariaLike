#pragma once
#include "../interfaces/InterfaceDU.hpp"
#include "../scenes/GameScene.hpp"
#include "../scenes/MenuInitialScene.hpp"

class Game : public InterfaceDU
{
private:
    std::unique_ptr<GameScene> GS;
    std::unique_ptr<MenuInitialScene> MIS;

public:
    Game();

    void update();
    void draw();
};