

function CreateTileMap(fileName)

local file = io.open(fileName, "r")

result = {}
pattern = "%S+"
for i=1,10,1 do
	local temp = file:read("l")
	for word in string.gmatch(temp, pattern) do
 	 table.insert(result, word)
	end
end

for i =0,9,1 do
print(" ")
	for j=0,9,1 do
 		nr = j+i*10
		io.write(result[nr + 1])
	end
end
file:close()


--offset is equal to the height width
offset = 32.0
startPositionX = 0.0
startPositionY = 0.0

for i=0,9,1 do

print(" ")
startPositionX = 0.0
	for j=0,9,1 do

	id = scene.CreateEntity()
	scene.SetComponent(id, "position", startPositionX, startPositionY)
	scene.SetComponent(id, "mesh", 0)
	io.write("x: ",startPositionX, " y: ", startPositionY , ", ")
	startPositionX = startPositionX + offset
	end
startPositionY = startPositionY + offset
end
end

--Used to change a specific tile to another type
function ChangeTile(Id, type)


		
end