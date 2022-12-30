def function hitBall(entity, startX, startY, endX, endY)

	-- CALCULATIONS FOR DIRECTION
	xVel = math.max(startX - endX, 200)
	yVel = math.max(startY - endY, 200)

	scene.SetComponent(entity, "velocity", xVel, yVel)
	scene.SetComponent(entity, "moveScript")
end
