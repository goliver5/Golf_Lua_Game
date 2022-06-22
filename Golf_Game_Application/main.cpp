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

	State* state = new Menu();
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
			state = new Menu();
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
		default:
			break;
		}
	}

	//bool running = true;
	//while (running)
	//{
	//	//Update Game
	//	//Render Game
	//	std::cout << "[C++] Update" << std::endl;
	//}



	//entt::registry registry;

	//entt::entity entity = registry.create();

	//struct Physics
	//{
	//	float VelocityY;
	//	float GravityFactorY;
	//};

	//struct Position
	//{
	//	float Y;
	//};

	//registry.emplace<Position>(entity, 100.f);
	//registry.emplace<Physics>(entity, 0.f, -9.82f);

	//auto view = registry.view<Position, Physics>();

	//float delta = 0.001254f;
	//int count = 0;

	//for (int i = 0; i < 5; i++)
	//{
	//	view.each([&](Position& position, Physics& physics)
	//		{
	//			position.Y += physics.VelocityY * delta; //Change to delta
	//			physics.VelocityY += physics.GravityFactorY * delta; //Change to delta
	//			count++;
	//		}
	//	);


	//	Position& position = registry.get<Position>(entity);
	//	std::cout << "Position: " << position.Y << std::endl;
	//	std::getchar();
	//}
	

	//std::cout << "Count: " << count << std::endl;
	return 0;
}