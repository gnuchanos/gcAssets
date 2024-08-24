extends Spatial


var speed = 5

func _process(delta):
	if !Globalvar.ConsoleMode:
		if Globalvar.Character == 0:
			if Input.is_action_pressed("w"):
				$wheel.rotation.z += speed * delta
			elif Input.is_action_pressed("s"):
				$wheel.rotation.z -= speed * delta
