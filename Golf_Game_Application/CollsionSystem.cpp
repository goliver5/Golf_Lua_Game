#include "CollsionSystem.h"
#include "CollisionComponent.h"
#include "Position.h"
#include "LuaExtraFunctions.h"
#include "VelocityData.h"
#include "TileComponent.h"
#include "WallComponent.h"
#include "raylib.h"
#include "PlayerComponent.h"

CollisionSystem::CollisionSystem(lua_State* L)
{
    this->L = L;    
}

CollisionSystem::~CollisionSystem()
{
}

bool CollisionSystem::OnUpdate(entt::registry& registry, float delta)
{
    auto playerView = registry.view<PlayerComponent, Position>();
    playerView.each([&](PlayerComponent& playerComp, Position& playerComPos)
    {
        auto collisionView = registry.view<Position, WallComponent, TileComponent>();
        Vector2 playerPos;
        playerPos.x = playerComPos.posX;
        playerPos.y = playerComPos.posY;
        Rectangle rec;
        collisionView.each([&](Position& pos, WallComponent& wallComp, TileComponent& tileComp)
            {
                Vector2 entityPos;
                rec.height = tileComp.height;
                rec.width = tileComp.width;
                rec.x = pos.posX;
                rec.y = pos.posY;

                if (rec.x == playerPos.x && rec.y == playerPos.y);
                else if (CheckCollisionCircleRec(playerPos, 10, rec))
                {
                    CollisionComponent col(0, 0, false, false);

                    //Checks vector from player position to center of rectangle
                    if (abs(playerPos.x - (rec.x + rec.width / 2)) < abs(playerPos.y - (rec.y + rec.height / 2)))
                    {
                        col.y = true;
                    }
                    else
                    {
                        col.x = true;
                    }

                    registry.emplace_or_replace<CollisionComponent>((entt::entity)playerComp.playerID, col);
                }
            }
        );
    }
    );

    auto view = registry.view<VelocityData, CollisionComponent>();

    view.each([&](VelocityData& pos, CollisionComponent& col)
        {

            lua_rawgeti(L, LUA_REGISTRYINDEX, col.LuaTableRef);


            if (luaL_dofile(L, "golfball.lua") != 0)
            {
                //dump error
                std::cout << "error do file!\n";
            }

            lua_pushinteger(L, col.entity);
            lua_setfield(L, -2, "ID");

            lua_getfield(L, -1, "collide");
            lua_pushvalue(L, -2);
            bool x = col.x;
            bool y = col.y;
            lua_pushboolean(L, x);
            lua_pushboolean(L, y);

            if (lua_pcall(L, 3, 0, 0) != LUA_OK)
            {
                DumpError(L);
            }
            lua_pop(L, 1);
            lua_pop(L, 1);
        }
    );

    return false;
}
