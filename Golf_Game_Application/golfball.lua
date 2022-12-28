local golfball = {}
local constant = 1

function golfball:OnCreate()
	print("Golfball created!")
end

function golfball:OnUpdate(delta)
	local pos = scene.GetComponent(self.ID, "position")		
	pos.x = pos.x + delta * pos.velocityX
	pos.y = pos.y + delta * pos.velocityY
	pos.velocityX = math.max(pos.velocityX - delta * constant, 0)
	pos.velocityY = math.max(pos.velocityY - delta * constant, 0)
	scene.SetComponent(self.ID, "position", pos)
end

return golfball