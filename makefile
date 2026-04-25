GXX = g++

FILES = ./src/main.cpp ./src/game/Game.cpp ./src/scenes/GameScene.cpp ./src/world/World.cpp ./src/world/blocos/Bloco.cpp ./src/utils/Texturas.cpp ./src/player/Player.cpp ./src/inventario/Inventario.cpp ./src/inventario/itens/Iten.cpp ./src/scenes/MenuInitialScene.cpp ./src/menus/MenuInicial.cpp ./src/utils/gameState/GameState.cpp

FLAGS = -lRaylib -lOpengl32

OUTPUT = ./Terraria.exe

all:
	$(GXX) $(FILES) $(FLAGS) -o $(OUTPUT)

run: all
	$(OUTPUT)