#include "CollsionSystem.h"
#include "CollisionComponent.h"
#include "Position.h"
#include "LuaExtraFunctions.h"

CollisionSystem::CollisionSystem(lua_State* L)
{
    this->L = L;    
}

CollisionSystem::~CollisionSystem()
{
}

bool CollisionSystem::OnUpdate(entt::registry& registry, float delta)
{
    auto view = registry.view<Position, CollisionComponent>();

    view.each([&](Position& pos, CollisionComponent& col)
        {
            lua_pushcollision(L, col);
            //lua_pushvalue(L, -1);
            //int luaTableRef = luaL_ref(L, LUA_REGISTRYINDEX);
            //std::cout << "Testingigning\n";

            lua_rawgeti(L, LUA_REGISTRYINDEX, col.LuaTableRef);
            lua_getfield(L, -1, "collide");
            lua_pushvalue(L, -2);
            if (lua_pcall(L, 1, 0, 0) != LUA_OK)
            {
                //DumpError(L);
            }
            lua_pop(L, 1);

            //pos.posX += rightdata.speedX;
        }
    );

    return false;
}
