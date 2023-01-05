#include "Input.h"
#include "VelocityData.h"
#include "Position.h"

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

	//bool shot = (GetMousePosition().x != this->savedPos.x && GetMousePosition().y != this->savedPos.y);
	if (holding && !IsMouseButtonDown(MOUSE_BUTTON_LEFT))// && !r->all_of<VelocityData>((entt::entity)playerID))
	{
		if (!r->all_of<Position>((entt::entity)playerID)) return;
		VelocityData vel;
		
		//this->savedPos.x = this->r->get<Position>((entt::entity)playerID).posX;// - GetMousePosition().x);
		//this->savedPos.y = this->r->get<Position>((entt::entity)playerID).posY;// - GetMousePosition().y);
		vel.velocityX = (this->savedPos.x - GetMousePosition().x);
		vel.velocityY = (this->savedPos.y - GetMousePosition().y);
		r->emplace_or_replace<VelocityData>((entt::entity)playerID, vel);
		this->savedPos = GetMousePosition();
		holding = false;
	}
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
