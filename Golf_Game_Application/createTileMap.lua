

function CreateTileMap(fileName)

local file = io.open(fileName, "r")


result = {}
pattern = "%S+"
for i = 0,14,1 do
local temp = file:read("l")
for word in string.gmatch(temp, pattern) do
 	 table.insert(result, word)
	end
end

for i =1,14,1 do
print(" ")
	for j=1,24,1 do
 		nr = j + i *25
		--io.write("j: ",j)
		--io.write(result[nr])
	end
end
file:close()

--offset is equal to the height width
offset = 32.0
startPositionX = 0.0
startPositionY = 0.0

local holeCounter = 0




--print(" ")
for i=0, 14, 1 do
startPositionX = 0.0
	for j=0, 24, 1 do

	id = scene.CreateEntity()
	scene.SetComponent(id, "position", startPositionX, startPositionY)
	scene.SetComponent(id, "mesh", 0, result[j+i*25])
	scene.SetComponent(id, "tile")
	if(tostring(result[j+i*25])  == tostring(1)) then scene.SetComponent(id, "wall") end
	if( tostring(result[j+i*25])  == tostring(2)) then 
		scene.SetComponent(id, "hole", holeCounter) 
		holeCounter = holeCounter + 1
		print(holeCounter) 
	end
	--io.write("x: ",startPositionX, " y: ", startPositionY , ", ")
	startPositionX = startPositionX + offset
	end
startPositionY = startPositionY + offset
end
end

--Used to change a specific tile to another type
function ChangeTile(Id, type)


		
end