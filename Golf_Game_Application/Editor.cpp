#include "Editor.h"

Editor::Editor(lua_State* L)
    :scene(Scene(L))
{
    this->L = L;
    scene.lua_openscene(L, &scene);
    tileMap.CreateTileMap(scene);
}

Editor::~Editor()
{
}

CURRENTSTATE Editor::update()
{
    if (IsKeyPressed(KEY_S))
    {
        //Add logic for saving
        std::cout << "SAVED FILE\n";
        tileMap.writeLevelToFile();
    }
    else if (IsKeyPressed(KEY_ESCAPE))
    {
        return CURRENTSTATE::MENU;
    }
    scene.Update(1.f/144.f);
    return CURRENTSTATE();
}

void Editor::render()
{
    scene.UpdateSystems(1.f/144.f);
    DrawText("Editor mode\nPress Mouse button to select a tile\nWhen selected, press Q, W or R to change the tile type\nPress S to save level\nESC to go back to menu", 10, 10, 20.f, WHITE);
    EndDrawing();
}
