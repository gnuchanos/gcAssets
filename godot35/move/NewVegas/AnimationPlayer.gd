extends AnimationPlayer


func _process(delta):
	if Input.is_action_pressed("w"):
		self.play("walk_loop")
	elif Input.is_action_pressed("s"):
		self.play("walk_loop")
	elif Input.is_action_pressed("left_m"):
		self.play("hi_loop")
	else:
		self.play("idl_loop")
