#pragma once

#include "WorldNow.hpp"
#include "../../inventario/itens/Iten.hpp"
#include <vector>
#include <string>
#include <memory>

class Bd
{
public:
    static int seed;
    static std::string file;
    static bool leu;
    static std::vector<WorldNow> blocks;
    static std::shared_ptr<Iten> itens[50];
    static void save();
    static void load(std::string &file);
};