#pragma once
#include "State.h"

class Menu : public State
{
private:


public:
	Menu();
	~Menu();

	// Inherited via State
	virtual CURRENTSTATE update() override;
	virtual void render() override;

};
