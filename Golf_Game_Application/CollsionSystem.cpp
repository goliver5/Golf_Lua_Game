#include "CollsionSystem.h"
#include "CollisionComponent.h"
#include "Position.h"
#include "LuaExtraFunctions.h"
#include "VelocityData.h"

CollisionSystem::CollisionSystem(lua_State* L)
{
    this->L = L;    
}

CollisionSystem::~CollisionSystem()
{
}

bool CollisionSystem::OnUpdate(entt::registry& registry, float delta)
{
    auto view = registry.view<VelocityData, CollisionComponent>();

    view.each([&](VelocityData& pos, CollisionComponent& col)
        {
            //std::cout << "LOLOWDOADAW\n";
            //return;

            lua_rawgeti(L, LUA_REGISTRYINDEX, col.LuaTableRef);


            if (luaL_dofile(L, "golfball.lua") != 0)
            {
                //dump error
                std::cout << "error do file!\n";
            }

            dump(L);
            std::cout << "ENTITY: " << col.entity << "\n";
            lua_pushinteger(L, col.entity);
            lua_setfield(L, -2, "ID");

            lua_getfield(L, -1, "collide");
            lua_pushvalue(L, -2);
            if (lua_pcall(L, 1, 0, 0) != LUA_OK)
            {
                DumpError(L);
            }
            lua_pop(L, 1);
        }
    );

    return false;
}
