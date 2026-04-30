#include "Bd.hpp"
#include <fstream>

std::vector<WorldNow> Bd::blocks = {};
std::string Bd::file = "";
bool Bd::leu = false;
int Bd::seed = 0;

void Bd::load(std::string &file)
{
    Bd::file = file;

    std::ifstream arquive(file, std::ios::binary);
    if (!arquive)
    {
        return;
    }

    size_t size = 0;

    if (!arquive.read(reinterpret_cast<char *>(&size), sizeof(size)))
    {
        return;
    }

    blocks.resize(size);
    if (!arquive.read(reinterpret_cast<char *>(blocks.data()), size * sizeof(WorldNow)))
    {
        return;
    }

    if (!arquive.read(reinterpret_cast<char *>(&seed), sizeof(seed)))
    {
        return;
    }
}

void Bd::save()
{
    if (file.empty())
    {
        return;
    }

    std::ofstream arquive(file, std::ios::binary);
    if (!arquive)
    {
        return;
    }

    size_t size = blocks.size();

    arquive.write(reinterpret_cast<const char *>(&size), sizeof(size));
    arquive.write(reinterpret_cast<const char *>(blocks.data()), size * sizeof(WorldNow));
    arquive.write(reinterpret_cast<const char *>(&seed), sizeof(seed));
}