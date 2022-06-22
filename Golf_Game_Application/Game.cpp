#include "Game.h"
#include <iostream>


Game::Game()
{


    ballPosition = { (float)800 / 2, (float)450 / 2 };

}

Game::~Game()
{
}

CURRENTSTATE Game::update()
{
	//std::cout << "Game state!\n";
    if (IsKeyDown(KEY_RIGHT)) ballPosition.x += 2.0f;
    if (IsKeyDown(KEY_LEFT)) ballPosition.x -= 2.0f;
    if (IsKeyDown(KEY_UP)) ballPosition.y -= 2.0f;
    if (IsKeyDown(KEY_DOWN)) ballPosition.y += 2.0f;
	return CURRENTSTATE::NOCHANGE;
}

void Game::render()
{
    BeginDrawing();

    ClearBackground(RAYWHITE);

    DrawText("move the ball with arrow keys", 10, 10, 20, DARKGRAY);

    DrawCircleV(ballPosition, 50, MAROON);

    EndDrawing();
}