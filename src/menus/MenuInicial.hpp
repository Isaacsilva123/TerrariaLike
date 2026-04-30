#pragma once
#include "../interfaces/InterfaceAll.hpp"
#include <vector>
#include <string>

class MenuInicial : public InterfaceAll
{
private:
    Rectangle bounds;
    std::vector<std::string> fileNames;
    Vector2 scroll = {0, 0};
public:
    MenuInicial();
    void draw();
    void ler();
};
