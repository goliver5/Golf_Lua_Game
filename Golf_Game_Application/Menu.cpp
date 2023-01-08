#include "Menu.h"
#include <iostream>

Menu::Menu(lua_State* L)
	:scene(Scene(L))
{
	if (!IsWindowReady()) InitWindow(screenWidth, screenHeight, "Golf Game");
	SetTargetFPS(144);

	std::cout << "\n----------------------------\nLua console:\n\n";

	scene.lua_openscene(L, &scene);
	if (luaL_dofile(L, "test.lua")) std::cout << "WRONG\n";

	Tilemap tilemap;
	//tilemap.CreateTileMap(scene);
	//tilemap.MapCounter();
}

Menu::~Menu()
{
}

CURRENTSTATE Menu::update()
{
	CURRENTSTATE state = CURRENTSTATE::NOCHANGE;
	
	state = scene.Update(1.f / 144.f);
	scene.UpdateSystems(1.f/144.f);

	return state;
}

void Menu::render()
{
	DrawText("Use the mouse to move the ball", 10, 10, 20, DARKGRAY);
	DrawText("Play game", 800 / 2 - 50, 450 / 4 - 50, 20, DARKGRAY);
	DrawText("Exit Game", 800 / 2 - 240, 480 / 2 + 50, 20, DARKGRAY);
	DrawText("Credits", 800 / 2 + 150, 480 / 2 + 50, 20, DARKGRAY);
	DrawText("Editor", 800 / 2 - 130, 480 / 2 - 75, 20, DARKGRAY);
	EndDrawing();
}
