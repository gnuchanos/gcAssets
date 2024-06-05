extends KinematicBody2D


var speed = 300
var velocity = Vector2.ZERO

func _process(delta):
	self.position.y = clamp(self.position.y, 100, 497.527)
	if Input.is_action_pressed("w"):
		velocity.y = -speed
	elif Input.is_action_pressed("s"):
		velocity.y = speed
	else:
			velocity.y = 0
	velocity = move_and_slide(velocity, Vector2.UP)




