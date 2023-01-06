#include "Tilemap.h"
#include <iostream>
#include "Position.h"
#include "MeshComponent.h"
#include "WallComponent.h"
#include "HoleComponent.h"

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
				scene.SetComponent<WallComponent>(entity, offset, offset);
			}
			else if (tileNumber == TileMesh::HOLE)
			{
				tileType = "../Sprites/hole1.png";
				scene.SetComponent<HoleComponent>(entity, offset, offset, holeCounter++);
			}

			// 0 as middle arg because we only need squares for tilemap
			scene.SetComponent<MeshComponent>(entity, 0, tileType);
			
			std::cout << ", X: " << startposX << " Y: " << startposY;

			startposX += offset;
		}
		startposY += offset;
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
