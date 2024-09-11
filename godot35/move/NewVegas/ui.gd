extends Control

onready var InputTEXT = $input

func _process(delta):
	if Input.is_action_just_pressed("console") and !Globalvar.ConsoleMode:
		InputTEXT.text = ""
		Globalvar.ConsoleMode = true
		Input.set_mouse_mode(Input.MOUSE_MODE_VISIBLE)
	elif Input.is_action_just_pressed("console") and Globalvar.ConsoleMode:
		Globalvar.ConsoleMode = false
		Input.set_mouse_mode(Input.MOUSE_MODE_HIDDEN)
		Input.set_mouse_mode(Input.MOUSE_MODE_CAPTURED)

	if Input.is_action_just_pressed("enter"):
		if InputTEXT.text == "wakeup":
			Globalvar.ConsoleMode = false
		elif InputTEXT.text == "groom":
			get_tree().change_scene("res://scene/worldGameROOM.tscn")
			Globalvar.ConsoleMode = false
		elif InputTEXT.text == "ngroom":
			get_tree().change_scene("res://scene/WorldInGame.tscn")
			Globalvar.ConsoleMode = false
		elif InputTEXT.text == "zardis":
			get_tree().change_scene("res://scene/worldTardis.tscn")
			Globalvar.ConsoleMode = false
		InputTEXT.text = ""

	if Globalvar.ConsoleMode:
		$input.visible = true
		$input.grab_focus()
	else:
		$input.visible = false
