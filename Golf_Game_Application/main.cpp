//Third party includes
#include "lua.hpp"
#include "raylib.h"
#include "entt\entt.hpp"

#include <iostream>
#include <thread>
#include <string>

//Game states
#include "Menu.h"
#include "Game.h"
#include "EndScreen.h"
#include "Credits.h"
#include "Editor.h"
#include "RightSystem.hpp"
#include "Position.h"
#include "VelocityData.h"
#include "Scene.h"
#include "Tilemap.h"


void DumpError(lua_State* L)
{
	if (lua_gettop(L) && lua_isstring(L, -1))
	{
		std::cout << "Lua error: " << lua_tostring(L, -1) << std::endl;
		lua_pop(L, 1);
	}

}

void ConsoleThreadFunction(lua_State* L)
{
	std::string input;
	while (true)
	{
		std::cout << "> ";
		std::getline(std::cin, input);

		if (luaL_dostring(L, input.c_str()) != LUA_OK)
		{
			DumpError(L);
		}
	}
}

int main()
{
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);

	std::thread consoleThread(ConsoleThreadFunction, L);

	InitWindow(800, 480, "Golf Game");

	State* state = new Menu(L);
	CURRENTSTATE currentState = CURRENTSTATE::NOCHANGE;

	while (state != nullptr)
	{
		switch (currentState)
		{
		case CURRENTSTATE::NOCHANGE:
			currentState = state->update();
			state->render();
			break;
		case CURRENTSTATE::EXIT:
			delete state;
			state = nullptr;
			break;
		case CURRENTSTATE::MENU:
			delete state;
			state = new Menu(L);
			currentState = CURRENTSTATE::NOCHANGE;
			break;
		case CURRENTSTATE::GAME:
			delete state;
			state = new Game();
			currentState = CURRENTSTATE::NOCHANGE;
			break;
		case CURRENTSTATE::ENDSCREEN:
			delete state;
			state = new EndScreen();
			currentState = CURRENTSTATE::NOCHANGE;
			break;
		case CURRENTSTATE::CREDITS:
			delete state;
			state = new Credits();
			currentState = CURRENTSTATE::NOCHANGE;
			break;
		case CURRENTSTATE::EDITOR:
			delete state;
			state = new Editor(L);
			currentState = CURRENTSTATE::NOCHANGE;
			break;
		default:
			break;
		}
	}

	consoleThread.detach();
	lua_close(L);
	CloseWindow();
	return 0;
}