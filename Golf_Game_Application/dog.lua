local dog = {}

dog.nrofbarks = 10
dog.type = "Uwu dog"

function dog:OnCreate()
	print("hp =", dog.hp, " dog created!", "dog type = ", dog.type)
end

function dog:OnUpdate(delta)
	dog.nrofbarks = dog.nrofbarks -1
	if dog.nrofbarks >= 0 then
		print("self.id = ", self.ID, "Woof nr: ", dog.nrofbarks)
	end
end

return dog