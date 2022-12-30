local golfball = {}
local constant = 1.0

function golfball:OnCreate()
	print("Golfball created!")
end

function golfball:OnUpdate(delta)
	local pos = scene.GetComponent(self.ID, "position")		
	local vel = scene.GetComponent(self.ID, "velocity")
	pos.x = pos.x + delta * vel.velocityX
	pos.y = pos.y + delta * vel.velocityY
	vel.velocityX = math.max(vel.velocityX - delta * constant, 0)
	vel.velocityY = math.max(vel.velocityY - delta * constant, 0)
	scene.SetComponent(self.ID, "position", pos)
	if (vel.velocityX == 0 and vel.velocityY == 0) 
	then
		print("Removed Velocity")
		scene.RemoveComponent(self.ID, "velocity")
	else	
		scene.SetComponent(self.ID, "velocity", vel)
	end
end

return golfball