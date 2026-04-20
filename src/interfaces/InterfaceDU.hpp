#pragma once
#include "InterfaceAll.hpp"

#define WORLD_SIZE 9000

class InterfaceDU : public InterfaceAll
{
public:
    void update();
    void draw();
};