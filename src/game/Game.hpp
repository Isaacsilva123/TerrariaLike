#pragma once
#include "../interfaces/InterfaceDU.hpp"
#include "../scenes/GameScene.hpp"
#include "../scenes/MenuInitialScene.hpp"

class Game : public InterfaceDU
{
public:
    std::unique_ptr<GameScene> GS;
    std::unique_ptr<MenuInitialScene> MIS;

    Game();

    void update();
    void draw();
};