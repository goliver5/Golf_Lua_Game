#include "RenderSystem.h"
#include "Position.h"
#include "raylib.h"
#include "PlayerComponent.h"

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
    auto view = registry.view<Position, MeshComponent>();

    BeginDrawing();
    ClearBackground(RAYWHITE);

    view.each([&](Position& pos, MeshComponent& mesh)
        {
            Vector2 meshPosition;
            meshPosition.x = pos.posX;
            meshPosition.y = pos.posY;
            
            if (mesh.usingMesh == EntityMesh::SQUARE)
            {
                DrawTexture(mesh.texture, meshPosition.x, meshPosition.y, WHITE);
            }
            else if (mesh.usingMesh == EntityMesh::CIRCLE)
            {
                DrawCircleV(meshPosition, 10, MAROON);
            }
           
        }
    );

    auto newView = registry.view<Position, MeshComponent, PlayerComponent>();
    newView.each([&](Position& pos, MeshComponent& mesh, PlayerComponent& plData)
        {
            Vector2 meshPosition;
            Color clr;
            clr.r = plData.r;
            clr.g = plData.g;
            clr.b = plData.b;
            clr.a = 255.f;

            meshPosition.x = pos.posX;
            meshPosition.y = pos.posY;
            DrawCircleV(meshPosition, 10, clr);
        }
    );


    inputClass->renderLine();

    return false;
}
