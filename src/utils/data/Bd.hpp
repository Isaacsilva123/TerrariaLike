#pragma once

#include "WorldNow.hpp"
#include <vector>
#include <string>

class Bd
{
public:
    static int seed;
    static std::string file;
    static bool leu;
    static std::vector<WorldNow> blocks;
    static void save();
    static void load(std::string &file);
};