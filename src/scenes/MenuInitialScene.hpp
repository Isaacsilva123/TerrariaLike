#pragma once
#include "../interfaces/InterfaceDU.hpp"
#include "../menus/MenuInicial.hpp"

class MenuInitialScene
{
private:
    std::unique_ptr<MenuInicial> menuI;

public:
    MenuInitialScene();
    void draw();
    void update();
};