

function CreateTileMap(fileName)

local file = io.open(fileName, "r")

local result = {}
pattern = "%S+"
for i = 0,14,1 do
local temp = file:read("l")
for word in string.gmatch(temp, pattern) do
 	 table.insert(result, word)
	end
end

for i =0,14,1 do
	print("")
	for j=0,24,1 do
 		nr = (j+1) + i *25
		--io.write("j: ",nr)
		--io.write(result[nr])
	end
end
file:close()

--offset is equal to the height width
offset = 32.0

--where we start making tiles from
local startPositionX = 0.0
local startPositionY = 0.0

local holeCounter = 0




--print(" ")
for i=0, 14, 1 do
startPositionX = 0.0
--print(" ")
	for j=0, 24, 1 do

	local id = scene.CreateEntity()
	scene.SetComponent(id, "position", startPositionX, startPositionY)
	scene.SetComponent(id, "mesh", 0, result[(j+1)+i*25])
	scene.SetComponent(id, "tile")
	if(tostring(result[(j+1)+i*25])  == tostring(1)) then scene.SetComponent(id, "wall") end
	if( tostring(result[(j+1)+i*25])  == tostring(2)) then 
		scene.SetComponent(id, "hole", holeCounter) 
		holeCounter = holeCounter + 1
		--print(holeCounter) 
	end
	--io.write(j+i*25 .. ", ")
	--io.write("x: ",startPositionX, " y: ", startPositionY , ", ")
	startPositionX = startPositionX + offset
	end
startPositionY = startPositionY + offset
end
end

--Used to change a specific tile to another type
function ChangeTile(Id, type)
	a = scene.HasComponent(id, "wall")
	print(Id .. type)
	if (scene.HasComponent(Id, "wall")) then print("HAS COMPOENENT") scene.RemoveComponent(Id, "wall") end
	if (scene.HasComponent(Id, "hole")) then scene.RemoveComponent(Id, "hole") end
	scene.SetComponent(Id, type)
	newMesh = 0
	if (tostring(type) == "wall") then newMesh = 1 end
	if (tostring(type) == "hole") then newMesh = 2 end
	scene.SetComponent(Id, "mesh", 0, newMesh)
		
end