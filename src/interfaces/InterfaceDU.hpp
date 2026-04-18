#pragma once
#include "InterfaceAll.hpp"

#define WORLD_SIZE 100

class InterfaceDU : public InterfaceAll
{
public:
    void update();
    void draw();
};