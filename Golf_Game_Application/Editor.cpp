#include "Editor.h"

Editor::Editor(lua_State* L)
    :scene(Scene(L)), inputClass(Input(L))
{
    this->L = L;
    scene.lua_openscene(L, &scene);
    scene.addInputClassToRenderSystem(&inputClass);
    inputClass.setRegistry(scene.getRegistry());
    if (luaL_dofile(L, "createTileMap.lua")) std::cout << "CREATE TILE MAP ERROR\n";

    lua_getglobal(L, "CreateTileMap");
    lua_pushvalue(L, -1);
    lua_pushstring(L, "level1.glf");

    if (lua_pcall(L, 1, 0, 0, 0)) std::cout << "ERROR CREATE TILE MAP c++ ....\n";
    lua_pop(L, 1);
}

Editor::~Editor()
{
}

CURRENTSTATE Editor::update()
{
    inputClass.handleMouseClick();
    if (IsKeyPressed(KEY_S))
    {
        std::cout << "SAVED FILE\n";
        tileMap.writeLevelToFile(scene.GetTileIds(), "level1.glf");
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
    DrawText("Editor mode\nPress Left Mouse button to select a tile\nWhen selected, press Q, W or R to change the tile type\nPress S to save level\nESC to go back to menu", 10, 10, 20.f, BLACK);
    EndDrawing();
}
