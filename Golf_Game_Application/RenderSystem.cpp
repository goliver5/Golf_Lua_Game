#include "RenderSystem.h"
#include "Position.h"
#include "raylib.h"

RenderSystem::RenderSystem(lua_State* L)
    :inputClass(nullptr)
{
    this->L = L;
}

void RenderSystem::addInputClass(Input* inputClass)
{
    this->inputClass = inputClass;
}

bool RenderSystem::OnUpdate(entt::registry& registry, float delta)
{
    //auto view = registry.view<rightData, Position>();
    auto view = registry.view<Position, MeshComponent>();

    BeginDrawing();
    ClearBackground(RAYWHITE);

    int i = 0;
    view.each([&](Position& pos, MeshComponent& mesh)
        {
            Vector2 meshPosition;
            meshPosition.x = pos.posX;
            meshPosition.y = pos.posY;

         


           

            if (i == 0) DrawCircleV(meshPosition, 10, MAROON);
            else
            {
                DrawRectangle(meshPosition.x, meshPosition.y, 32.f, 32.f, BLUE);
            }
            i++;
        }
    );

    DrawText("move the ball to Play Game and press A", 10, 10, 20, DARKGRAY);
    DrawText("Play game", 800 / 2 - 40, 450 / 4 - 5, 20, DARKGRAY);
    inputClass->renderLine();

    EndDrawing();

    return false;
}
