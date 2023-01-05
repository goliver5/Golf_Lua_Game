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
	
	if (vel.velocityX < 0) then
		vel.velocityX = math.min(vel.velocityX + delta * constant, 0)
	else
		vel.velocityX = math.max(vel.velocityX - delta * constant, 0)
	end
	
	if (vel.velocityY < 0) then
		vel.velocityY = math.min(vel.velocityY + delta * constant, 0)
	else
		vel.velocityY = math.max(vel.velocityY - delta * constant, 0)
	end

	scene.SetComponent(self.ID, "position", pos)
	if (vel.velocityX == 0 and vel.velocityY == 0) 
	then
		print("Removed Velocity")
		scene.RemoveComponent(self.ID, "velocity")
	else	
		scene.SetComponent(self.ID, "velocity", vel)
	end
end

function golfball:collide(x, y)
	print(self.ID)
	local pos = scene.GetComponent(self.ID, "position")
	local vel = scene.GetComponent(self.ID, "velocity")
	-- local collisionInfo = scene.GetComponent(self.ID, "collision")	
	if (x) then
		pos.x = pos.x - vel.velocityX * 4/144 
		vel.velocityX = -vel.velocityX * 0.9
	end
	if (y) then
		pos.y = pos.y - vel.velocityY * 4/144 
		vel.velocityY = -vel.velocityY * 0.9
	end
	
	scene.SetComponent(self.ID, "position", pos)
	scene.SetComponent(self.ID, "velocity", vel)
	scene.RemoveComponent(self.ID, "collision")
end

return golfball