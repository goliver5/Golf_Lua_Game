#include "Game.h"
#include <iostream>


Game::Game(lua_State* L)
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
    std::string arg = "test UWU";
    //lua_pushstring(L,"TEST UWU");

    if (lua_pcall(L, 1, 0, 0, 0)) std::cout << "ERROR CREATE TILE MAP c++ ....\n";

    if (luaL_dofile(L, "test.lua")) std::cout << "CREATE pLaYeR ERROR\n";

}

Game::~Game()
{
}

CURRENTSTATE Game::update()
{

    CURRENTSTATE state = CURRENTSTATE::NOCHANGE;

    inputClass.playerClick();
    inputClass.checkCollision();
    //inputClass.handleMouseClick();

    state = scene.Update(1.f / 144.f);
    state = inputClass.wonHole();
    scene.UpdateSystems(1.f / 144.f);

    if (state == CURRENTSTATE::GAME) state = CURRENTSTATE::MENU;
    return state;
}

void Game::render()
{
    BeginDrawing();

    ClearBackground(RAYWHITE);

    EndDrawing();
}