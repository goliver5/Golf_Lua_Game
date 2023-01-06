#include "Menu.h"
#include <iostream>

Menu::Menu(lua_State* L)
	:scene(Scene(L))
{
	if (!IsWindowReady()) InitWindow(screenWidth, screenHeight, "Golf Game");
	SetTargetFPS(144);

	std::cout << "\n----------------------------\nLua console:\n\n";
	ballPosition = { (float)800 / 2, (float)480 / 2 };

	scene.lua_openscene(L, &scene);
	if (luaL_dofile(L, "test.lua")) std::cout << "WRONG\n";

	Tilemap tilemap;
	tilemap.CreateTileMap(scene);
	tilemap.MapCounter();
}

Menu::~Menu()
{
}

CURRENTSTATE Menu::update()
{
	CURRENTSTATE state = CURRENTSTATE::NOCHANGE;
	if (IsKeyDown(KEY_RIGHT)) ballPosition.x += 2.0f;
	if (IsKeyDown(KEY_LEFT)) ballPosition.x -= 2.0f;
	if (IsKeyDown(KEY_UP)) ballPosition.y -= 2.0f;
	if (IsKeyDown(KEY_DOWN)) ballPosition.y += 2.0f;
	if (IsKeyPressed(KEY_A) && (ballPosition.x > screenWidth/2-40 && ballPosition.x < screenWidth / 2 + 40 && ballPosition.y > screenHeight / 4 - 10 && ballPosition.y < screenHeight / 4 + 10)) return CURRENTSTATE::GAME;
	
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
	EndDrawing();
	//BeginDrawing();
	//
	//ClearBackground(RAYWHITE);
	//
	//DrawText("move the ball to Play Game and press A", 10, 10, 20, DARKGRAY);
	//DrawText("Play game", screenWidth/2-40, screenHeight/4-5, 20, DARKGRAY);
	//
	//DrawCircleV(ballPosition, 10, MAROON);
	//
	//EndDrawing();
}
