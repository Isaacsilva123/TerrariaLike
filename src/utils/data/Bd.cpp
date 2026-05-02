#include "Bd.hpp"
#include <fstream>

std::vector<WorldNow> Bd::blocks = {};
std::string Bd::file = "";
bool Bd::leu = false;
int Bd::seed = 0;
std::shared_ptr<Iten> Bd::itens[50] = {};

void Bd::load(std::string &file)
{
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

    for (int i = 0; i < 50; i++)
    {
        bool exist;

        arquive.read(reinterpret_cast<char *>(&exist), sizeof(exist));

        if (exist)
        {
            Type t;
            int q;

            arquive.read(reinterpret_cast<char *>(&t), sizeof(t));
            arquive.read(reinterpret_cast<char *>(&q), sizeof(q));
            itens[i] = std::make_shared<Iten>(t);
            itens[i]->quantidade = q;
            
        }
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

    for (int i = 0; i < 50; i++)
    {
        bool exist = itens[i] != nullptr;

        arquive.write(reinterpret_cast<const char *>(&exist), sizeof(exist));

        if (exist)
        {
            Type t = itens[i]->tipo;
            int q = itens[i]->quantidade;
            arquive.write(reinterpret_cast<const char *>(&t), sizeof(t));
            arquive.write(reinterpret_cast<const char *>(&q), sizeof(q));
        }
    }
}