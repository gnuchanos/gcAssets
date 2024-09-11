extends Spatial

var DoorOpen = false
var AreaEnter = false

func _ready():
	$"0".current = true

func _process(delta):

	if !Globalvar.ConsoleMode:
		if Input.is_action_just_pressed("1"):
			$"0".current = true
		elif Input.is_action_just_pressed("2"):
			$"1".current = true
		elif Input.is_action_just_pressed("3"):
			$"2".current = true

	if $"0".current:
		if Input.is_action_pressed("q"):
			$"0".rotate_y(1*delta)
		elif Input.is_action_pressed("e"):
			$"0".rotate_y(-1*delta)
	elif $"1".current:
		if Input.is_action_pressed("q"):
			$"1".rotate_y(1*delta)
		elif Input.is_action_pressed("e"):
			$"1".rotate_y(-1*delta)

	if AreaEnter:
		if Input.is_action_just_pressed("left") and !DoorOpen:
			$HomeDoor_bigBrother/door0/AnimationPlayer.play("door_open")
			DoorOpen = true
		elif Input.is_action_just_pressed("right") and DoorOpen:
			$HomeDoor_bigBrother/door0/AnimationPlayer.play_backwards("door_open")
			DoorOpen = false

func _on_door_body_entered(body):
	if body.name == "FPS":
		AreaEnter = true

func _on_door_body_exited(body):
	if body.name == "FPS":
		AreaEnter = false
