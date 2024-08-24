extends KinematicBody

var speed = 2
const ACCEL_DEFAULT = 7
const ACCEL_AIR = 1
onready var accel = ACCEL_DEFAULT
var gravity = 9.8

var mouse_sense = 0.3
var snap

var direction = Vector3()
var velocity = Vector3()
var gravity_vec = Vector3()
var movement = Vector3()

func _SwitchModel():
	if Input.is_action_just_pressed("Alt_Left"):
		if Globalvar.Character > 0:
			Globalvar.Character -= 1
	elif Input.is_action_just_pressed("Alt_Right"):
		if Globalvar.Character < 2:
			Globalvar.Character += 1
	if Globalvar.Character == 0:
		$new_vegas_securitron.visible = true
		$borderlands_claptrap.visible = false
		$core.visible = false
	elif Globalvar.Character == 1:
		$borderlands_claptrap.visible = true
		$new_vegas_securitron.visible = false
		$core.visible = false
	elif Globalvar.Character == 2:
		$core.visible = true
		$borderlands_claptrap.visible = false
		$borderlands_claptrap.visible = false

func _ready():
	#hides the cursor
	Input.set_mouse_mode(Input.MOUSE_MODE_CAPTURED)

func _input(event):
	if !Globalvar.ConsoleMode:
		#get mouse input for camera rotation
		if event is InputEventMouseMotion:
			rotate_y(deg2rad(-event.relative.x * mouse_sense))

func _process(delta):
	_SwitchModel()

func _physics_process(delta):
	if !Globalvar.ConsoleMode:
		#get keyboard input
		direction = Vector3.ZERO
		var h_rot = global_transform.basis.get_euler().y
		var f_input = Input.get_action_strength("w") - Input.get_action_strength("s")
		var h_input = Input.get_action_strength("a") - Input.get_action_strength("d")
		direction = Vector3(0, 0, f_input).rotated(Vector3.UP, h_rot).normalized()

	#jumping and gravity
	if is_on_floor():
		snap = -get_floor_normal()
		accel = ACCEL_DEFAULT
		gravity_vec = Vector3.ZERO
	else:
		snap = Vector3.DOWN
		accel = ACCEL_AIR
		gravity_vec += Vector3.DOWN * gravity * delta

	#make it move
	velocity = velocity.linear_interpolate(direction * speed, accel * delta)
	movement = velocity + gravity_vec
	move_and_slide_with_snap(movement, snap, Vector3.UP)
