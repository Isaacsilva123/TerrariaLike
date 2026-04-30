#include "MenuInicial.hpp"
#include "../includes/raygui.h"
#include "../utils/gameState/GameState.hpp"
#include "../utils/data/Bd.hpp"
#include <filesystem>

namespace fs = std::filesystem;

MenuInicial::MenuInicial()
{
    float width = 200;
    float height = 50;
    float x = (GetScreenWidth() / 2.f) - (width / 2.f);
    float y = (GetScreenHeight() / 2.f) - (height / 2.f);

    bounds = {x, y, width, height};

    ler();
}

void MenuInicial::ler()
{
    fileNames.clear();

    if (!fs::exists("mundos"))
        fs::create_directory("mundos");

    for (auto &entry : fs::directory_iterator("mundos"))
    {
        if (entry.is_regular_file() && entry.path().extension() == ".bin")
        {
            fileNames.push_back(entry.path().stem().string());
        }
    }
}

void MenuInicial::draw()
{
    Rectangle full = {0, 0, (float)GetScreenWidth(), (float)GetScreenHeight()};

    if (GameState::stt == STATE::MENUI)
    {
        if (GuiButton(bounds, "Play"))
        {
            GameState::stt = STATE::MENUW;
        }
        return;
    }
    else
    {

        Rectangle content = {
            0,
            0,
            full.width,
            40 + (float)fileNames.size() * 35};

        Rectangle view;

        GuiScrollPanel(full, NULL, content, &scroll, &view);

        BeginScissorMode(view.x, view.y, view.width, view.height);

        Rectangle criarBtn = {
            view.x + 10,
            view.y + 5,
            view.width - 20,
            30};

        if (GuiButton(criarBtn, "Criar Mundo"))
        {
            Bd::seed = rand() % 2000;
            Bd::file = TextFormat("mundos/mundo%i.bin", (int)fileNames.size());
            Bd::save();

            ler();
        }

        int start = scroll.y / 35;
        int end = start + (view.height / 35) + 2;

        for (int i = start; i < end && i < fileNames.size(); i++)
        {
            float y = view.y + 40 + i * 35 - scroll.y;

            Rectangle item = {
                view.x + 10,
                y,
                view.width - 20,
                30};

            if (GuiButton(item, fileNames[i].c_str()))
            {
                std::string path = "mundos/" + fileNames[i] + ".bin";
                Bd::load(path);
                GameState::stt = STATE::GAME;
            }
        }

        EndScissorMode();
    }
}