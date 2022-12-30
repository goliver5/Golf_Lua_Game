local entity = {}

function entity:collide()
	print("test")
	local pos = scene.GetComponent(self.ID, "position")
	local collisionInfo = scene.GetComponent(self.ID, "collision")	
	if (collisionInfo.xCol) pos.velocityX = -pos.velocityX * 0.9
	if (collisionInfo.yCol) pos.velocityY = -pos.velocityY * 0.9
	scene.SetComponent(self.ID, "position", pos)
	scene.RemoveComponent(self.ID, "collision")
end

return entity