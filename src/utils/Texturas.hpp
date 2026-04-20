#pragma once
#include <raylib.h>

struct Texturas
{
public:
    static Texture2D terra;
    static Texture2D player;
    static Texture2D grama;
    static Texture2D pedra;
    static Texture2D inventario;
    static Texture2D selected;
    static Texture2D tronco;
    static Texture2D folha;
    static Texture2D tabua;
    static void LoadALL();
    static void UnloadALL();
};