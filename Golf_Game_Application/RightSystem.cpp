#include "RightSystem.hpp"
#include "VelocityData.h"
#include "Position.h"
#include <iostream>
#include "LuaExtraFunctions.h"
#include "MoveScript.h"

RightSystem::RightSystem(lua_State* L)
{
    this->L = L;
}

bool RightSystem::OnUpdate(entt::registry& registry, float delta)
{
    
    //auto view = registry.view<rightData, Position>();
    auto view = registry.view<Position, VelocityData, MoveScript>();

    view.each([&](Position& pos, VelocityData& velData, MoveScript& script)
        {
            lua_rawgeti(L, LUA_REGISTRYINDEX, script.LuaTableRef);
            if (luaL_dofile(L, script.ScriptPath) != 0)
            {
                //dump error
                std::cout << "error do file!\n";
            }
            lua_pushinteger(L, script.entity);
            lua_setfield(L, -2, "ID");

            //std::cout << "awdawwadwwa\n";
            lua_getfield(L, -1, "OnUpdate");
            lua_pushvalue(L, -2);
            lua_pushnumber(L, delta);
            if (lua_pcall(L, 2, 0, 0) != LUA_OK) 
            {
                DumpError(L);
            }
            
            lua_pop(L, 1);

            //pos.posX += rightdata.speedX;
        }
    );

    return false;
}
