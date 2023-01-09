#include "Input.h"
#include "VelocityData.h"
#include "Position.h"
#include "MeshComponent.h"
#include "CollisionComponent.h"
#include "WallComponent.h"
#include "HoleComponent.h"
#include "TileComponent.h"
#include <string>
#include "LuaExtraFunctions.h"

Input::Input(lua_State* L)
	:playerID(0), holding(false)
{
	this->savedPos.x = 0.f;
	this->savedPos.y = 0.f;
	this->L = L;
}

Input::~Input()
{
}

CURRENTSTATE Input::wonHole(int* playerStrokes)
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
			rec.x = pos.posX;
			rec.y = pos.posY;

			if (rec.x == playerPos.x && rec.y == playerPos.y);
			else if (CheckCollisionCircleRec(playerPos, 10, rec))
			{
				if (holeComp.state == 0) state = CURRENTSTATE::GAME;
				else if (holeComp.state == 1) state = CURRENTSTATE::EDITOR;
				else if (holeComp.state == 2) state = CURRENTSTATE::EXIT;
				else state = CURRENTSTATE::CREDITS;
				if (playerStrokes != nullptr) *playerStrokes = strokes;
				strokes = 0;
			}
		}
	);
	return state;
}

void Input::setRegistry(entt::registry* registry)
{
	this->r = registry;
}

void Input::handleMouseClick()
{
	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
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
		if (luaL_dofile(L, "createTileMap.lua")) std::cout << "CREATE TILE MAP ERROR\n";

		lua_getglobal(L, "ChangeTile");
		lua_pushvalue(L, -1);
		lua_pushnumber(L, this->selectedEntity);
		lua_pushstring(L, "");

		if (lua_pcall(L, 2, 0, 0, 0)) std::cout << "ERROR CREATE TILE MAP c++ ....\n";
		this->selectedEntity = -1;
		lua_pop(L, 1);
	}
	if (this->selectedEntity > -1 && IsKeyPressed(KEY_W))
	{
		std::cout << "CHANGE TILE COMPONENT TO 1\n";
		if (luaL_dofile(L, "createTileMap.lua")) std::cout << "CREATE TILE MAP ERROR\n";
		
		lua_getglobal(L, "ChangeTile");
		lua_pushvalue(L, -1);
		lua_pushnumber(L, this->selectedEntity);
		lua_pushstring(L, "wall");
		
		if (lua_pcall(L, 2, 0, 0, 0)) std::cout << "ERROR CREATE TILE MAP c++ ....\n";
		this->selectedEntity = -1;
		lua_pop(L, 1);
	}
	if (this->selectedEntity > -1 && IsKeyPressed(KEY_E))
	{
		std::cout << "CHANGE TILE COMPONENT TO 2\n";
		if (luaL_dofile(L, "createTileMap.lua")) std::cout << "CREATE TILE MAP ERROR\n";

		lua_getglobal(L, "ChangeTile");
		lua_pushvalue(L, -1);
		lua_pushnumber(L, this->selectedEntity);
		lua_pushstring(L, "hole");

		if (lua_pcall(L, 2, 0, 0, 0)) std::cout << "ERROR CREATE TILE MAP c++ ....\n";
		this->selectedEntity = -1;
		lua_pop(L, 1);
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
		if (luaL_dofile(L, "inputs.lua")) std::cout << "INPUT FILE ERROR\n";

		lua_getglobal(L, "hitBall");
		lua_pushvalue(L, -1);
		lua_pushnumber(L, playerID);
		lua_pushnumber(L, this->savedPos.x);
		lua_pushnumber(L, this->savedPos.y);
		lua_pushnumber(L, GetMousePosition().x);
		lua_pushnumber(L, GetMousePosition().y);

		if (lua_pcall(L, 5, 0, 0, 0)) DumpError(L);
		lua_pop(L, 1);

		this->savedPos = GetMousePosition();
		holding = false;
		strokes++;
	}
}

void Input::renderLine()
{
	std::string strokeCounter = "Strokes: " + std::to_string(strokes);
	DrawText(strokeCounter.c_str(), 650, 10, 20, DARKGRAY);
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
