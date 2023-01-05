
scene.CreateEntity()
scene.SetComponent(0, "position")
scene.SetComponent(0, "mesh", 0)
scene.SetComponent(0, "moveScript")
scene.SetComponent(0, "velocity")

--scene.CreateEntity()
--scene.SetComponent(1, "position", 100, 100)
--scene.SetComponent(1, "mesh", 0)
--scene.SetComponent(1, "moveScript")

for i = 1, 11, 1 do
	scene.CreateEntity()
	scene.SetComponent(i, "position", 32*i, 100)
	scene.SetComponent(i, "mesh", 0)
	scene.SetComponent(i, "moveScript")
end

for i = 11, 21, 1 do
	scene.CreateEntity()
	scene.SetComponent(i, "position", 32*(i-10), 200)
	scene.SetComponent(i, "mesh", 0)
	scene.SetComponent(i, "moveScript")
end