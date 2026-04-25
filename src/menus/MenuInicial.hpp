#pragma once
#include "../interfaces/InterfaceAll.hpp"

class MenuInicial : public InterfaceAll
{
private:
    Rectangle bounds;
public:
    MenuInicial();
    void draw();
};
