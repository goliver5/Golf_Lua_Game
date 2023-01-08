#include "Credits.h"
#include <iostream>


Credits::Credits()
{
}

Credits::~Credits()
{
}

CURRENTSTATE Credits::update()
{
    if (IsKeyPressed(KEY_ESCAPE)) return CURRENTSTATE::MENU;
    return CURRENTSTATE::NOCHANGE;
}

void Credits::render()
{
    BeginDrawing();

    ClearBackground(RAYWHITE);

    DrawText("Press ESC to go to menu", 10, 10, 20, DARKGRAY);
    DrawText("Made by:", 10, 140, 30, DARKGRAY);
    DrawText("Oliver O.J", 10, 170, 20, DARKGRAY);
    DrawText("Morgan W", 10, 190, 20, DARKGRAY);


    EndDrawing();
}