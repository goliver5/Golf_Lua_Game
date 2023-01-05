-- local entity = {}

function createCollisionComp()
	print("Collision component created")
end

function collide()
	print(self.ID)
	local pos = scene.GetComponent(self.ID, "position")
	local vel = scene.GetComponent(self.ID, "velocity")
	local collisionInfo = scene.GetComponent(self.ID, "collision")	
	if (collisionInfo.xCol) then
		pos.x = pos.x - vel.velocityX * 1/144 
		vel.velocityX = -vel.velocityX * 0.9
	end
	if (collisionInfo.yCol) then
		pos.y = pos.y - vel.velocityY * 1/144 
		vel.velocityY = -vel.velocityY * 0.9
	end
	
	scene.SetComponent(self.ID, "position", pos)
	scene.SetComponent(self.ID, "velocity", vel)
	scene.RemoveComponent(self.ID, "collision")
end

-- return entity