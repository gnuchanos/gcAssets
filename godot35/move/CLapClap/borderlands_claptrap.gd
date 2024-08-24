extends Spatial

var speed = 5
var SleepMode = false
var idlMode = true

func _process(delta):
	if !Globalvar.ConsoleMode:
		if Globalvar.Character == 1:
			if idlMode and !SleepMode:
				if Input.is_action_pressed("w"):
					idlMode = false
				elif Input.is_action_pressed("s"):
					idlMode = false
			if Input.is_action_just_released("w") or Input.is_action_just_released("s"):
				idlMode = true

			if Input.is_action_just_pressed("r") and !SleepMode:
				SleepMode = true
				Globalvar.ConsoleMode = true

			if !Globalvar.ConsoleMode:
				SleepMode = false

			if !idlMode:
				if Input.is_action_pressed("w"):
					$clapClap.play("2_walk_loop")
					$wheel001.rotation.z += speed * delta
				elif Input.is_action_pressed("s"):
					$clapClap.play_backwards("2_walk_loop")
					$wheel001.rotation.z -= speed * delta
			else:
				if !SleepMode:
					$clapClap.play("1_idl_loop")
				else:
					$clapClap.play("0_sleep_loop")
