GXX = g++
FILES = ./src/main.cpp ./src/game/Game.cpp ./src/world/World.cpp ./src/world/blocos/Bloco.cpp ./src/utils/Texturas.cpp ./src/player/Player.cpp ./src/inventario/Inventario.cpp ./src/inventario/itens/Iten.cpp
FLAGS = -lRaylib -lOpengl32
OUTPUT = ./Terraria.exe

all:
	$(GXX) $(FILES) $(FLAGS) -o $(OUTPUT)

run: all
	$(OUTPUT)