#include "Menu.h"
#include <iostream>

Menu::Menu()
{
}

Menu::~Menu()
{
}

CURRENTSTATE Menu::update()
{
	std::cout << "Menu state!\n";
	return CURRENTSTATE::NOCHANGE;
}

void Menu::render()
{
}
