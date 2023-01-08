#pragma once
#include "State.h"

class EndScreen : public State
{
private:
	int strokes;

public:
	EndScreen(int strokes);
	~EndScreen();

	// Inherited via State
	virtual CURRENTSTATE update() override;
	virtual void render() override;

};