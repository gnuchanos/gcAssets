extends Control


func _ready():
	$sound.play()

func _process(delta):
	if !$sound.playing:
		$sound.play()

	if Input.is_action_just_pressed("esc"):
		get_tree().change_scene("res://scene/mainMenu.tscn")
