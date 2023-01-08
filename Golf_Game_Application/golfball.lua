local golfball = {}
local constant = 150

function golfball:OnCreate()
	print("Golfball created!")
end

function golfball:OnUpdate(delta)
	local pos = scene.GetComponent(self.ID, "position")		
	local vel = scene.GetComponent(self.ID, "velocity")
	pos.x = pos.x + delta * vel.velocityX
	pos.y = pos.y + delta * vel.velocityY
	speed = math.sqrt(vel.velocityX*vel.velocityX + vel.velocityY*vel.velocityY)
	newSpeed = speed - delta * constant
	ratio = newSpeed/speed
	if (speed > 5) then
		vel.velocityX = vel.velocityX * ratio
		vel.velocityY = vel.velocityY * ratio
		scene.SetComponent(self.ID, "velocity", vel)
	else
		scene.RemoveComponent(self.ID, "velocity")
		scene.RemoveComponent(self.ID, "moveScript")
	end
	scene.SetComponent(self.ID, "position", pos)
end

function golfball:collide(x, y)
	local pos = scene.GetComponent(self.ID, "position")
	local vel = scene.GetComponent(self.ID, "velocity")
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