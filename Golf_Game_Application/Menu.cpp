#include "Menu.h"
#include <iostream>

Menu::Menu(lua_State* L)
	:scene(Scene(L)), inputClass(Input(L))
{
	if (!IsWindowReady()) InitWindow(screenWidth, screenHeight, "Golf Game");
	SetTargetFPS(144);

	std::cout << "\n----------------------------\nLua console:\n\n";

	scene.lua_openscene(L, &scene);
	if (luaL_dofile(L, "test.lua")) std::cout << "WRONG\n";
	scene.addInputClassToRenderSystem(&inputClass);
	inputClass.setRegistry(scene.getRegistry());

	if (luaL_dofile(L, "createTileMap.lua")) std::cout << "CREATE TILE MAP ERROR\n";

	lua_getglobal(L, "CreateTileMap");
	lua_pushvalue(L, -1);
	lua_pushstring(L, "menu.glf");

	if (lua_pcall(L, 1, 0, 0, 0)) std::cout << "ERROR CREATE TILE MAP c++ ....\n";
	lua_pop(L, 1);
	
	Tilemap tilemap;
}

Menu::~Menu()
{
}

CURRENTSTATE Menu::update()
{
	CURRENTSTATE state = CURRENTSTATE::NOCHANGE;

	inputClass.playerClick();

	state = scene.Update(1.f / 144.f);
	state = inputClass.wonHole();
	scene.UpdateSystems(1.f/144.f);

	return state;
}

void Menu::render()
{
	DrawText("Use the mouse to move the ball", 10, 10, 20, DARKGRAY);
	DrawText("Play game", 800 / 2 - 18, 450 / 4 - 50, 20, DARKGRAY);
	DrawText("Exit Game", 800 / 2 - 208, 480 / 2 + 50, 20, DARKGRAY);
	DrawText("Credits", 800 / 2 + 182, 480 / 2 + 50, 20, DARKGRAY);
	DrawText("Editor", 800 / 2 - 98, 480 / 2 - 75, 20, DARKGRAY);
	EndDrawing();
}
