extends Node2D

@onready var yaw: Node2D = $yaw
var yaw_mag: float = 0.0


func _ready() -> void:
	Input.set_mouse_mode(Input.MOUSE_MODE_CAPTURED)


func _unhandled_input(event: InputEvent) -> void:
	# Clicking the game viewport re-captures mouse if unlocked
	if event is InputEventMouseButton and event.pressed:
		if Input.get_mouse_mode() != Input.MOUSE_MODE_CAPTURED:
			Input.set_mouse_mode(Input.MOUSE_MODE_CAPTURED)


func _input(event: InputEvent) -> void:
	# Toggle mouse lock with Escape key when not consumed by UI
	if event is InputEventKey and event.pressed and not event.echo:
		if event.keycode == KEY_ESCAPE:
			if Input.get_mouse_mode() == Input.MOUSE_MODE_CAPTURED:
				Input.set_mouse_mode(Input.MOUSE_MODE_VISIBLE)
			else:
				Input.set_mouse_mode(Input.MOUSE_MODE_CAPTURED)
			get_viewport().set_input_as_handled()
			return

	if event is InputEventMouseMotion and Input.get_mouse_mode() == Input.MOUSE_MODE_CAPTURED:
		yaw_mag += -event.relative.x


func _physics_process(delta: float) -> void:
	# Follow vehicle if player is in one, otherwise follow active player
	if PMS.current_vehicle != null:
		global_position = PMS.current_vehicle.global_position
	else:
		global_position = PMS.active_protag_pos

	yaw.rotate(yaw_mag * delta * PMS.mouse_sens)
	
	# Update 2D direction vector for PMS tracking
	PMS.looking_dir = Vector2.from_angle(yaw.global_rotation)
	
	yaw_mag = lerp(yaw_mag, 0.0, 0.2)
