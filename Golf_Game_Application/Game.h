#pragma once
#include "State.h"

class Game : public State
{
private:


public:
	Game();
	~Game();

	// Inherited via State
	virtual CURRENTSTATE update() override;
	virtual void render() override;

};