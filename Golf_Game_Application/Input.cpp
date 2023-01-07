#include "Input.h"
#include "VelocityData.h"
#include "Position.h"
#include "MeshComponent.h"
#include "CollisionComponent.h"
#include "WallComponent.h"
#include "HoleComponent.h"
#include "TileComponent.h"

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

CURRENTSTATE Input::wonHole()
{
	CURRENTSTATE state = CURRENTSTATE::NOCHANGE;

	auto view = r->view<Position, HoleComponent, TileComponent>();
	Vector2 playerPos;
	playerPos.x = this->r->get<Position>((entt::entity)playerID).posX;
	playerPos.y = this->r->get<Position>((entt::entity)playerID).posY;

	Rectangle rec;
	view.each([&](Position& pos, HoleComponent& holeComp, TileComponent& tileComp)
		{
			Vector2 entityPos;
			rec.height = tileComp.height;
			rec.width = tileComp.width;
			rec.x = pos.posX;// - rec.height / 2.f;
			rec.y = pos.posY;// - rec.width / 2.f;

			if (rec.x == playerPos.x && rec.y == playerPos.y);
			else if (CheckCollisionCircleRec(playerPos, 10, rec))
			{
				if (holeComp.state == 0) state = CURRENTSTATE::GAME;
				else if (holeComp.state == 1) state = CURRENTSTATE::EDITOR;
				else if (holeComp.state == 2) state = CURRENTSTATE::EXIT;
				else state = CURRENTSTATE::CREDITS;
			}
		}
	);
	return state;
}

void Input::handleMouseClick()
{
	if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
	{
		auto view = r->view<Position, TileComponent>();
		Vector2 mousePos = GetMousePosition();

		view.each([&](Position& pos, TileComponent& tileComp)
			{
				if (pos.posX < mousePos.x && pos.posX + tileComp.width > mousePos.x
					&& pos.posY < mousePos.y && pos.posY + tileComp.height > mousePos.y)
				{
					std::cout << "TILE ENTITY ID: " << tileComp.entityID << "\nPos: (" << pos.posX << ", "
						<< pos.posY << ")\nDimensions: (" << tileComp.width << ", " << tileComp.height << ")\n";
					this->selectedEntity = tileComp.entityID;
				}
			}
		);
	}
	
	if (this->selectedEntity > -1 && IsKeyPressed(KEY_Q))
	{
		std::cout << "CHANGE TILE COMPONENT TO 0\n";
		this->selectedEntity = -1;
	}
	if (this->selectedEntity > -1 && IsKeyPressed(KEY_W))
	{
		std::cout << "CHANGE TILE COMPONENT TO 1\n";
		this->selectedEntity = -1;
	}
	if (this->selectedEntity > -1 && IsKeyPressed(KEY_E))
	{
		std::cout << "CHANGE TILE COMPONENT TO 2\n";
		this->selectedEntity = -1;
	}
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
		vel.velocityX = 2.f * (this->savedPos.x - GetMousePosition().x);
		vel.velocityY = 2.f * (this->savedPos.y - GetMousePosition().y);
		float vectorLength = vel.velocityX * vel.velocityX + vel.velocityY * vel.velocityY;
		if (vectorLength > 100000)
		{
			vel.velocityX *= (sqrt(100000 / vectorLength));
			vel.velocityY *= (sqrt(100000 / vectorLength));
		}
		r->emplace_or_replace<VelocityData>((entt::entity)playerID, vel);
		this->savedPos = GetMousePosition();
		holding = false;
	}
}

void Input::checkCollision()
{
	auto view = r->view<Position, WallComponent, TileComponent>();
	Vector2 playerPos;
	playerPos.x = this->r->get<Position>((entt::entity)playerID).posX;
	playerPos.y = this->r->get<Position>((entt::entity)playerID).posY;

	Rectangle rec;
	view.each([&](Position& pos, WallComponent& wallComp, TileComponent& tileComp)
		{
			Vector2 entityPos;
			rec.height = tileComp.height;
			rec.width = tileComp.width;
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
		Vector2 vec;
		vec.x = (this->savedPos.x - GetMousePosition().x);
		vec.y = (this->savedPos.y - GetMousePosition().y);

		float vectorLength = vec.x * vec.x + vec.y * vec.y;
		if (vectorLength > 100000)
		{
			vec.x *= (sqrt(100000 / vectorLength));
			vec.y *= (sqrt(100000 / vectorLength));
		}
		Vector2 end;
		end.x = start.x + 0.5f * vec.x;
		end.y = start.y + 0.5f * vec.y;

		
		

		DrawCircle(this->savedPos.x, this->savedPos.y, 5, MAGENTA);
		DrawLineEx(start, end, 2.f, RED);
	}
}
