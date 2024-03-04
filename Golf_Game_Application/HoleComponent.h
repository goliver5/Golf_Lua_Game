#pragma once
#include "base.h"

struct HoleComponent : public base
{
	int state;

	HoleComponent(int state = 0)
	{
		this->state = state;
	}
};