extends CharacterBody3D

@onready var yaw: Node3D = $yaw
@onready var pitch: Node3D = $yaw/pitch

var jump_imp: float = 10.0
var walk_vel: float = 9.0
var gravity: float = 20.0
var mouse_sens: float = 1.0
var pitch_mag: float
var yaw_mag: float

func _ready() -> void:
	Input.mouse_mode = Input.MOUSE_MODE_CAPTURED

func _input(event: InputEvent) -> void:
	if event is InputEventMouseMotion and Input.mouse_mode == Input.MOUSE_MODE_CAPTURED:
		yaw_mag = -event.relative.x
		pitch_mag = -event.relative.y
	
	if event.is_action_pressed("ui_cancel") and Input.get_mouse_mode() == Input.MOUSE_MODE_CAPTURED:
		Input.set_mouse_mode(Input.MOUSE_MODE_VISIBLE)
	if event is InputEventMouseButton and Input.get_mouse_mode() == Input.MOUSE_MODE_VISIBLE:
		Input.set_mouse_mode(Input.MOUSE_MODE_CAPTURED)


func _process(delta: float) -> void:
	yaw.rotate_y(yaw_mag * delta * mouse_sens)
	pitch.rotate_x(pitch_mag * delta * mouse_sens)
	pitch.rotation.x = clamp(pitch.rotation.x, deg_to_rad(-75), deg_to_rad(45) )
	yaw_mag = 0.0
	pitch_mag = 0.0


func _physics_process(delta: float) -> void:
	if Input.is_action_just_pressed("jump") and is_on_floor():
		velocity.y = lerp(velocity.y, jump_imp, 0.9)
	
	if not is_on_floor():
		velocity.y -= gravity * delta

	var input_dir = Input.get_vector("left", "right", "forward", "backward")
	var direction = (yaw.global_transform.basis * Vector3(input_dir.x, 0, input_dir.y)).normalized()
	
	if direction:
		velocity.x = lerp(velocity.x, direction.x * walk_vel, 0.1)
		velocity.z = lerp(velocity.z, direction.z * walk_vel, 0.1)
	else:
		velocity.x = lerp(velocity.x, 0.0, 0.1)
		velocity.z = lerp(velocity.z, 0.0, 0.1)
	
	move_and_slide()
