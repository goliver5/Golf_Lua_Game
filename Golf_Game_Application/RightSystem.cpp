#include "RightSystem.hpp"
#include "RightData.h"
#include "Position.h"
#include <iostream>

RightSystem::RightSystem(lua_State* L)
{
    this->L = L;
}

bool RightSystem::OnUpdate(entt::registry& registry, float delta)
{
    
    //auto view = registry.view<rightData, Position>();
    auto view = registry.view<Position>();

    view.each([&](Position& pos)
        {
            lua_rawgeti(L, LUA_REGISTRYINDEX, pos.LuaTableRef);
            lua_getfield(L, -1, "OnUpdate");
            lua_pushvalue(L, -2);
            lua_pushnumber(L, delta);
            if (lua_pcall(L, 2, 0, 0) != LUA_OK) 
            {
                std::cout << "Something went wrong :(\n";//DumpError(L);
            }
            lua_pop(L, 1);

            //pos.posX += rightdata.speedX;
        }
    );

    return false;
}
