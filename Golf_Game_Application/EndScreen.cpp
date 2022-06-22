#include "EndScreen.h"
#include <iostream>

EndScreen::EndScreen()
{
}

EndScreen::~EndScreen()
{
}

CURRENTSTATE EndScreen::update()
{
	std::cout << "EndScreen state!\n";
	return CURRENTSTATE::NOCHANGE;
}

void EndScreen::render()
{
}