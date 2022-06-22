#pragma once

enum class CURRENTSTATE { NOCHANGE, EXIT, MENU, GAME, ENDSCREEN};

class State
{
public:
	State();
	~State();

	virtual CURRENTSTATE update() = 0;
	virtual void render() = 0;
};