#include "RenderSystem.h"
#include "Position.h"
#include "raylib.h"

RenderSystem::RenderSystem(lua_State* L)
{
    this->L = L;
}

bool RenderSystem::OnUpdate(entt::registry& registry, float delta)
{
    //auto view = registry.view<rightData, Position>();
    auto view = registry.view<Position, MeshComponent>();

    BeginDrawing();
    ClearBackground(RAYWHITE);

    view.each([&](Position& pos, MeshComponent& mesh)
        {
            Vector2 meshPosition;
            meshPosition.x = pos.posX;
            meshPosition.y = pos.posY;

         


           

            DrawCircleV(meshPosition, 10, MAROON);

            
        }
    );

    DrawText("move the ball to Play Game and press A", 10, 10, 20, DARKGRAY);
    DrawText("Play game", 800 / 2 - 40, 450 / 4 - 5, 20, DARKGRAY);

    EndDrawing();

    return false;
}
