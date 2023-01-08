#include "EndScreen.h"
#include <iostream>
#include "raylib.h"
#include <string>

EndScreen::EndScreen(int strokes)
	:strokes(strokes)
{
}

EndScreen::~EndScreen()
{
}

CURRENTSTATE EndScreen::update()
{
	CURRENTSTATE state = CURRENTSTATE::NOCHANGE;
	if (IsKeyPressed(KEY_ESCAPE)) state = CURRENTSTATE::MENU;
	return state;
}

void EndScreen::render()
{
	std::string strokeCounter = "You completed the level!\nESC to go back to menu\nYou completed the course in " + std::to_string(strokes) + " strokes!";
	BeginDrawing();
	ClearBackground(RAYWHITE);
	DrawText(strokeCounter.c_str(), 300, 50, 20, DARKGRAY);
	EndDrawing();
}