#include <iostream>
#include <thread>
#include <Windows.h>
#include <string>

#include "lua.hpp"

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
	while (GetConsoleWindow())
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

	bool running = true;
	while (running)
	{
		//Update Game
		//Render Game
		std::cout << "[C++] Update" << std::endl;
	}

	std::cout << "Hello world!\n";
	return 0;
}