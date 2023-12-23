#include "DogSystem.h"
#include "LuaExtraFunctions.h"
#include "raylib.h"
#include "TestBehaviour.h"

DogSystem::DogSystem(lua_State* L)
{
    this->L = L;
}

DogSystem::~DogSystem()
{
}

bool DogSystem::OnUpdate(entt::registry& registry, float delta)
{
    auto view = registry.view<TestBehaviour>();

    view.each([&](TestBehaviour& behaviour)
        {
            
    lua_rawgeti(L, LUA_REGISTRYINDEX, behaviour.luaRef);


    if (luaL_dofile(L, "dog.lua") != 0)
    {
        //dump error
        std::cout << "error do file! DOG.LUA\n";
    }
    else {
        lua_getfield(L, -1, "update");
        lua_setfield(L, -3, "update");
        lua_pop(L, 1);
    }

        lua_getfield(L, -1, "OnUpdate");
        lua_pushvalue(L, -2);

        lua_pushnumber(L, delta);

        if (lua_type == LUA_TNIL) {
            lua_pop(L, 1);
            return;
        }

        if (lua_pcall(L, 2, 0, 0) != LUA_OK)
        {
            DumpError(L);
        }
        lua_pop(L, 1);
        }
    );

    return false;
}
