GXX = g++

FILES = ./src/main.cpp ./src/game/Game.cpp ./src/scenes/GameScene.cpp ./src/world/World.cpp ./src/world/blocos/Bloco.cpp ./src/utils/Texturas.cpp ./src/player/Player.cpp ./src/inventario/Inventario.cpp ./src/inventario/itens/Iten.cpp ./src/scenes/MenuInitialScene.cpp ./src/menus/MenuInicial.cpp ./src/utils/gameState/GameState.cpp ./src/utils/data/Bd.cpp

LIBS = -lraylib -lopengl32 -lgdi32 -lwinmm

FLAGS = $(LIBS)

RELEASE_FLAGS = -O2 -s -mwindows $(LIBS)

OUTPUT = Terraria.exe

all:
	$(GXX) $(FILES) $(FLAGS) -o $(OUTPUT)

run: all
	./$(OUTPUT)

release:
	$(GXX) $(FILES) $(RELEASE_FLAGS) -o $(OUTPUT)

run_release: release
	./$(OUTPUT)