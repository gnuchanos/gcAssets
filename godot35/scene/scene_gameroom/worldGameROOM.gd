extends Spatial

func _process(delta):
	if !Globalvar.ConsoleMode:
		if Input.is_action_just_pressed("1"):
			$"0".current = true
		elif Input.is_action_just_pressed("2"):
			$"1".current = true

		if Input.is_action_pressed("left"):
			$"1".rotate_y(1*delta)
		elif Input.is_action_pressed("right"):
			$"1".rotate_y(-1*delta)
