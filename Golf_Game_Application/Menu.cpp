#include "Menu.h"
#include <iostream>

Menu::Menu()
{
	InitWindow(screenWidth, screenHeight, "Golf Game");
	SetTargetFPS(144);

	ballPosition = { (float)800 / 2, (float)450 / 2 };
}

Menu::~Menu()
{
}

CURRENTSTATE Menu::update()
{
	if (IsKeyDown(KEY_RIGHT)) ballPosition.x += 2.0f;
	if (IsKeyDown(KEY_LEFT)) ballPosition.x -= 2.0f;
	if (IsKeyDown(KEY_UP)) ballPosition.y -= 2.0f;
	if (IsKeyDown(KEY_DOWN)) ballPosition.y += 2.0f;
	if (IsKeyPressed(KEY_A) && (ballPosition.x > screenWidth/2-40 && ballPosition.x < screenWidth / 2 + 40 && ballPosition.y > screenHeight / 4 - 10 && ballPosition.y < screenHeight / 4 + 10)) return CURRENTSTATE::GAME;
	return CURRENTSTATE::NOCHANGE;
}

void Menu::render()
{
	BeginDrawing();

	ClearBackground(RAYWHITE);

	DrawText("move the ball to Play Game and press A", 10, 10, 20, DARKGRAY);
	DrawText("Play game", screenWidth/2-40, screenHeight/4-5, 20, DARKGRAY);

	DrawCircleV(ballPosition, 10, MAROON);

	EndDrawing();
}
