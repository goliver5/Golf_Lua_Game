function hitBall(ID, startX, startY, endX, endY)
	local maxSpeed = 500
	local vel = {}
	vel.velocityX = 2.0 * (startX  - endX)
	vel.velocityY = 2.0 * (startY  - endY)
	local vectorLength = vel.velocityX * vel.velocityX + vel.velocityY * vel.velocityY
	if (vectorLength > maxSpeed * maxSpeed ) then
		vel.velocityX = vel.velocityX * (maxSpeed  / math.sqrt(vectorLength))
		vel.velocityY = vel.velocityY * (maxSpeed  / math.sqrt(vectorLength))
	end

	scene.SetComponent(ID, "velocity", vel)
	scene.SetComponent(ID, "moveScript")
end
