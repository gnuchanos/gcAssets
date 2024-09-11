extends Spatial

var doorOpen = false
var AreaDoor = false

func _ready():
	Input.set_mouse_mode(Input.MOUSE_MODE_CAPTURED)

func _process(delta):
	if !Globalvar.ConsoleMode:
		if Input.is_action_just_pressed("1"):
			$"1".current = true
		elif Input.is_action_just_pressed("2"):
			$"2".current = true
		elif Input.is_action_just_pressed("3"):
			$"3".current = true
		elif Input.is_action_just_pressed("4"):
			$"4".current = true

		if AreaDoor:
			if Input.is_action_just_pressed("e") and !doorOpen:
					$StaticBody/AnimationPlayer.play("open")
					$studio/AnimationPlayer.play("OpenTardisDoor")
					doorOpen = true
			elif Input.is_action_just_pressed("e") and doorOpen:
					$StaticBody/AnimationPlayer.play_backwards("open")
					$studio/AnimationPlayer.play_backwards("OpenTardisDoor")
					doorOpen = false

func _on_doorArea_body_entered(body):
	if body.name == "FPS":
		AreaDoor = true
func _on_doorArea_body_exited(body):
	if body.name == "FPS":
		AreaDoor = false
