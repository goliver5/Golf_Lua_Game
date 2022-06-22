#pragma once
#include "State.h"

class EndScreen : public State
{
private:


public:
	EndScreen();
	~EndScreen();

	// Inherited via State
	virtual CURRENTSTATE update() override;
	virtual void render() override;

};