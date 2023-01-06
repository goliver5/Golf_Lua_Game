#pragma once
#include "State.h"
#include "raylib.h"

class Credits : public State
{
private:

public:
	Credits();
	~Credits();

	// Inherited via State
	virtual CURRENTSTATE update() override;
	virtual void render() override;
};