#include "Tilemap.h"
#include <iostream>
#include "Position.h"
#include <fstream>
#include "MeshComponent.h"
#include "WallComponent.h"
#include "HoleComponent.h"
#include "TileComponent.h"

Tilemap::Tilemap()
{

}

Tilemap::~Tilemap()
{
}

bool Tilemap::CreateTileMap(Scene& scene)
{
	// Top left corner from where we start the tilemap
	float startposX = 0.0f;
	float startposY = 0.0f;

	//size to move components must be equal to size
	float offset = 32.0f;
	int holeCounter = 0;

	std::cout << "\ntype tile values\n";
	for (int i = 0; i < HEIGHT; i++)
	{
		startposX = 0.0f;

		std::cout << std::endl;
		for (int j = 0; j < WIDTH; j++)
		{
			//place in array
			int tileNumber = tileMap[j + i * WIDTH];

			int entity = scene.CreateEntity();

			if (scene.HasComponents<Position>(entity))
			{
				scene.RemoveComponent<Position>(entity);
			}
			if (scene.HasComponents<Mesh>(entity))
			{
				scene.RemoveComponent<Mesh>(entity);
			}
			scene.SetComponent<Position>(entity, startposX, startposY);

			std::string tileType;
			if (tileNumber == TileMesh::GROUND)
			{
				tileType = "../Sprites/ground.png";
			}
			else if (tileNumber == TileMesh::WALL)
			{
				tileType = "../Sprites/wall.png";
				scene.SetComponent<WallComponent>(entity);
			}
			else if (tileNumber == TileMesh::HOLE)
			{
				tileType = "../Sprites/hole1.png";
				scene.SetComponent<HoleComponent>(entity, holeCounter++);
			}

			// 0 as middle arg because we only need squares for tilemap
			//scene.SetComponent<MeshComponent>(entity, 0, tileType);
			scene.SetComponent<TileComponent>(entity, entity, offset, offset);
			tileMapID[j + i * WIDTH] = entity;

			std::cout << ", X: " << startposX << " Y: " << startposY;

			startposX += offset;
		}
		startposY += offset;
	}

	std::cout << "\nID for tilemap\n";
	for (int i = 0; i < WIDTH*HEIGHT; i++)
	{
		std::cout << tileMapID[i] << " ";
		if ((i + 1) % WIDTH == 0) std::cout << "\n";
	}
	std::cout << "\nEND TILE VALUES\n";
	return false;
}

void Tilemap::MapCounter()
{
	std::cout << "\START TILE COUNT\n";
	for (int i = 0; i < HEIGHT; i++)
	{
		std::cout << std::endl;
		for (int j = 0; j < WIDTH; j++)
		{
			int tileNumber = j + i * WIDTH;
			std::cout << tileNumber << ", ";
		}
	}
	std::cout << "\nEND TILES\n";
}

void Tilemap::writeLevelToFile(std::string fileName)
{
	std::ofstream file;
	file.open(fileName);
	if (file.is_open())
	{
		for (int i = 0; i < HEIGHT; i++)
		{
			for (int j = 0; j < WIDTH; j++)
			{
				file << tileMap[j + i * WIDTH];
				if (j - 1 < WIDTH) file << " ";
			}
			if (i < HEIGHT - 1) file << "\n";
		}
	}
	file.close();
}
