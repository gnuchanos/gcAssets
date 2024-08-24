extends Spatial

var flyMODE = false
var Speed = 5
func _process(delta):
	if !Globalvar.ConsoleMode:
		if Globalvar.Character == 2:
			if Input.is_action_just_pressed("f") and !flyMODE:
				$Armature/Skeleton/body.visible = false
				$wheel.visible = false
				flyMODE = true
			elif Input.is_action_just_pressed("f") and flyMODE:
				$Armature/Skeleton/body.visible = true
				$wheel.visible = true
				flyMODE = false

			if flyMODE:
				$coreAnim.play("1_idl_fly")
			else:
				$coreAnim.play("0_idl")

			if Input.is_action_pressed("w"):
				$wheel.rotation.z += Speed * delta
			elif Input.is_action_pressed("s"):
				$wheel.rotation.z -= Speed * delta
