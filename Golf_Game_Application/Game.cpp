#include "Game.h"
#include <iostream>


Game::Game(lua_State* L, int* strokes)
    :scene(Scene(L)), inputClass(Input(L)), strokes(strokes)
{
    this->L = L;
    scene.lua_openscene(L, &scene);
    scene.addInputClassToRenderSystem(&inputClass);
    inputClass.setRegistry(scene.getRegistry());
    if (luaL_dofile(L, "initiatePlayer.lua")) std::cout << "CREATE pLaYeR ERROR\n";
    if (luaL_dofile(L, "createTileMap.lua")) std::cout << "CREATE TILE MAP ERROR\n";

    lua_getglobal(L, "CreateTileMap");
    lua_pushvalue(L, -1);
    lua_pushstring(L, "level1.glf");

    if (lua_pcall(L, 1, 0, 0, 0)) std::cout << "ERROR CREATE TILE MAP c++ ....\n";
    lua_pop(L, 1);

}

Game::~Game()
{
}

CURRENTSTATE Game::update()
{

    CURRENTSTATE state = CURRENTSTATE::NOCHANGE;

    inputClass.playerClick();

    state = scene.Update(1.f / 144.f);
    state = inputClass.wonHole(strokes);
    scene.UpdateSystems(1.f / 144.f);

    if (state != CURRENTSTATE::NOCHANGE) state = CURRENTSTATE::ENDSCREEN;
    return state;
}

void Game::render()
{
    BeginDrawing();

    ClearBackground(RAYWHITE);

    EndDrawing();
}