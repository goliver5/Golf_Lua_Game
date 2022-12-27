local golfball = {}

function golfball:OnCreate()
	print("Golfball created!")
end

function golfball:OnUpdate(delta)
	local pos = scene.GetComponent(self.ID, "position") 
	pos.x = pos.x + delta
	scene.SetComponent(self.ID, "position", pos)
end

return golfball