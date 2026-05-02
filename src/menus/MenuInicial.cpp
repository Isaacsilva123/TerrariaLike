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
    nomeDigitado = true;

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
        Rectangle full = {0, 0, (float)GetScreenWidth(), (float)GetScreenHeight()};

        Rectangle content = {
            0,
            0,
            full.width,
            40 + (float)fileNames.size() * 40};

        Rectangle view;

        GuiScrollPanel(full, NULL, content, &scroll, &view);

        BeginScissorMode(view.x, view.y, view.width, view.height);

        Rectangle criarBtn = {
            view.x + 15,
            view.y + 5,
            view.width - 30,
            30};

        if (GuiButton(criarBtn, "Criar Mundo"))
        {
            nomeDigitado = false;
        }

        for (int i = 0; i < (int)fileNames.size(); i++)
        {
            float y = view.y + 40 + i * 40 + scroll.y;

            Rectangle item = {
                view.x + 15,
                y,
                view.width - 30,
                30};

            if (GuiButton(item, fileNames[i].c_str()))
            {
                std::string path = "mundos/" + fileNames[i] + ".bin";
                Bd::file = path;
                Bd::load(path);
                GameState::stt = STATE::GAME;
            }
        }

        EndScissorMode();

        if (!nomeDigitado)
        {
            if (GuiTextBox(bounds, nomeDoMundo, 128, !nomeDigitado))
            {
                Bd::seed = rand() % 1000000;
                Bd::file = TextFormat("mundos/%s.bin", nomeDoMundo);
                nomeDoMundo[0] = '\0';
                Bd::save();

                ler();
                nomeDigitado = true;
            }
        }
    }
}