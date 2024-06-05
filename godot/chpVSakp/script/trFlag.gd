extends KinematicBody2D


var speed = 600
var velocity = Vector2.ZERO



func _physics_process(delta):
	if GlovalVAR.LeftPaddleHit:
		#print(GlovalVAR.LeftPaddleHit)
		if GlovalVAR.UpAndDown:
			if Input.is_action_pressed("w"):
				GlovalVAR.UpAndDown_send = 1
			elif Input.is_action_pressed("s"):
				GlovalVAR.UpAndDown_send = 2
			else:
				GlovalVAR.UpAndDown_send = 0
		if GlovalVAR.upAndDown_Bar_Hit == 0:
			if GlovalVAR.UpAndDown_send == 1:
				#print(GlovalVAR.UpAndDown_send , " ekstra 1 ")
				velocity.x = speed
				velocity.y = -speed/2
			elif GlovalVAR.UpAndDown_send == 2:
				#print(GlovalVAR.UpAndDown_send , " ekstra 2 ")
				velocity.x = speed
				velocity.y = speed/2
			else:
				#print(GlovalVAR.UpAndDown_send , " ekstra 0 ")
				velocity.x = speed
		elif GlovalVAR.upAndDown_Bar_Hit == 1:
			velocity.x = speed
			velocity.y = speed/2
		elif GlovalVAR.upAndDown_Bar_Hit == 2:
			velocity.x = speed
			velocity.y = -speed/2
	else:
		#print(GlovalVAR.LeftPaddleHit)
		if GlovalVAR.UpAndDown:
			if Input.is_action_pressed("ui_up"):
				GlovalVAR.UpAndDown_send = 1
			elif Input.is_action_pressed("ui_down"):
				GlovalVAR.UpAndDown_send = 2
			else:
				GlovalVAR.UpAndDown_send = 0
		if GlovalVAR.upAndDown_Bar_Hit == 0:
			if GlovalVAR.UpAndDown_send == 1:
				#print(GlovalVAR.UpAndDown_send , " ekstra 1 ")
				velocity.x = -speed
				velocity.y = -speed/2
			elif GlovalVAR.UpAndDown_send == 2:
				#print(GlovalVAR.UpAndDown_send , " ekstra 2 ")
				velocity.x = -speed
				velocity.y = speed/2
			else:
				#print(GlovalVAR.UpAndDown_send , " ekstra 0 ")
				velocity.x = -speed
		elif GlovalVAR.upAndDown_Bar_Hit == 1:
			velocity.x = -speed
			velocity.y = speed/2
			print("works 1 right")
		elif GlovalVAR.upAndDown_Bar_Hit == 2:
			velocity.x = -speed
			velocity.y = -speed/2
			print("works 2 right")


	velocity = move_and_slide(velocity, Vector2.UP)
