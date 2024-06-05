extends Node2D


var leftArea = false
var rightArea = false
onready var point = $Panel/VBoxContainer/HBoxContainer/point
onready var hitSound = $hitSound

func _ready():
	GlovalVAR.leftPoint = 0
	GlovalVAR.rightPoint = 0

func _process(delta):
	point.text = " | LeftCHP: " + str(GlovalVAR.leftPoint) + " | " + str(GlovalVAR.rightPoint) + " : RightAKP | "
	if GlovalVAR.leftPoint == 1:
		get_tree().change_scene("res://scene/chpWins.tscn")
	if  GlovalVAR.rightPoint == 1:
		get_tree().change_scene("res://scene/akpWins.tscn")

func _on_leftLimitPointArea_body_entered(body):
	if body.name == "trFlag":
		$trFlag.position.x = get_viewport().size.x/2
		$trFlag.position.y = get_viewport().size.y/2
		GlovalVAR.rightPoint += 1
func _on_rightLimitPointArea_body_entered(body):
	if body.name == "trFlag":
		rightArea = true
		GlovalVAR.leftPoint += 1
		$trFlag.position.x = get_viewport().size.x/2
		$trFlag.position.y = get_viewport().size.y/2


func _on_upBar_body_entered(body):
	if body.name == "trFlag":
		GlovalVAR.upAndDown_Bar_Hit = 1
		GlovalVAR.StillUp = true
		hitSound.play()
func _on_upBar_body_exited(body):
	if body.name == "trFlag":
		GlovalVAR.upAndDown_Bar_Hit = 1


func _on_bottomBar_body_entered(body):
	if body.name == "trFlag":
		GlovalVAR.upAndDown_Bar_Hit = 2
		GlovalVAR.UpAndDown = true
		hitSound.play()
func _on_bottomBar_body_exited(body):
	if body.name == "trFlag":
		GlovalVAR.upAndDown_Bar_Hit = 2

func _on_leftHit_body_entered(body):
	if body.name == "trFlag":
		GlovalVAR.LeftPaddleHit = true
		GlovalVAR.UpAndDown = true
		GlovalVAR.upAndDown_Bar_Hit = 0
		hitSound.play()
func _on_leftHit_body_exited(body):
	if body.name == "trFlag":
		GlovalVAR.UpAndDown = false


func _on_rightHit_body_entered(body):
	if body.name == "trFlag":
		GlovalVAR.LeftPaddleHit = false
		GlovalVAR.UpAndDown = true
		GlovalVAR.upAndDown_Bar_Hit = 0
		if !hitSound.playing:
			hitSound.play()
		print("play works or?")
func _on_rightHit_body_exited(body):
	if body.name == "trFlag":
		GlovalVAR.UpAndDown = false
