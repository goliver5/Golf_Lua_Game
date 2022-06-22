#include "Game.h"
#include <iostream>

Game::Game()
{
}

Game::~Game()
{
}

CURRENTSTATE Game::update()
{
	std::cout << "Game state!\n";
	return CURRENTSTATE::NOCHANGE;
}

void Game::render()
{
}