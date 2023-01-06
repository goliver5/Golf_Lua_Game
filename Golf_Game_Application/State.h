#pragma once

enum class CURRENTSTATE { NOCHANGE, EXIT, MENU, GAME, ENDSCREEN, CREDITS};

class State
{
public:
	State();
	~State();

	virtual CURRENTSTATE update() = 0;
	virtual void render() = 0;
};