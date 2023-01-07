
-- startPos is the topLeft position of tilemap, offset is the size of the tile
function CreateTileMap(fileName, startPos, offset)

	for i=1,2,1 do print("loop")
		for i=1,2,1 do print("loop")
		id = scene.CreateEntity()
		scene.SetCompononent(id, "TileComponent", id, tileType)
		print(id)
			
		end
	end
end


function ChangeTile(Id, type)
{
	if (scene.HasComponent(Id, "WallComponent")) do scene.RemoveComponent(0, "WallComponent)
	if (scene.HasComponent(Id, "HoleComponent")) do scene.RemoveComponent(0, "HoleComponent)
	scene.SetComponent(Id, type)
		
}



struct TileComponent
{
int entityId;
int tileType;
};