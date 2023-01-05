#include "Input.h"
#include "VelocityData.h"
#include "Position.h"
#include "MeshComponent.h"
#include "CollisionComponent.h"
#include "WallComponent.h"

Input::Input(entt::registry* registry)
	:playerID(0), holding(false)
{
	this->r = registry;
	this->savedPos.x = 0.f;
	this->savedPos.y = 0.f;
}

Input::~Input()
{
}

void Input::playerClick()
{
	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) this->savedPos = GetMousePosition();
	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
	{
		holding = true;
	}

	if (holding && !IsMouseButtonDown(MOUSE_BUTTON_LEFT))// && !r->all_of<VelocityData>((entt::entity)playerID))
	{
		if (!r->all_of<Position>((entt::entity)playerID)) return;
		VelocityData vel;
		
		//MOVE OVER TO LUA
		//this->savedPos.x = this->r->get<Position>((entt::entity)playerID).posX;// - GetMousePosition().x);
		//this->savedPos.y = this->r->get<Position>((entt::entity)playerID).posY;// - GetMousePosition().y);
		vel.velocityX = (this->savedPos.x - GetMousePosition().x);
		vel.velocityY = (this->savedPos.y - GetMousePosition().y);
		r->emplace_or_replace<VelocityData>((entt::entity)playerID, vel);
		this->savedPos = GetMousePosition();
		holding = false;
	}
}

void Input::checkCollision()
{
	auto view = r->view<Position, WallComponent>();
	Vector2 playerPos;
	playerPos.x = this->r->get<Position>((entt::entity)playerID).posX;
	playerPos.y = this->r->get<Position>((entt::entity)playerID).posY;

	Rectangle rec;
	view.each([&](Position& pos, WallComponent& wallComp)
		{
			Vector2 entityPos;
			rec.height = wallComp.height;
			rec.width = wallComp.width;
			rec.x = pos.posX;// - rec.height / 2.f;
			rec.y = pos.posY;// - rec.width / 2.f;

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

				r->emplace_or_replace<CollisionComponent>((entt::entity)playerID, col);
			}
		}
	);
}

void Input::renderLine()
{
	if (holding)
	{
		Vector2 start;
		start.x = this->r->get<Position>((entt::entity)playerID).posX;
		start.y = this->r->get<Position>((entt::entity)playerID).posY;
		Vector2 end;
		end.x = start.x + (this->savedPos.x - GetMousePosition().x);
		end.y = start.y + (this->savedPos.y - GetMousePosition().y);


		DrawCircle(this->savedPos.x, this->savedPos.y, 5, MAGENTA);
		DrawLine(start.x, start.y, end.x, end.y, RED);
	}
}
