extends Node

@export var input_dir: Vector2 = Vector2.ZERO
@export var yaw_mag: float
@export var pitch_mag: float
@export var mouse_sens: float = 1
@export var current_protag_chosen: int
@export var current_protag_wanted: int
@export var protag_1_pos: Vector3
@export var last_protag_controlled: int
@export var looking_basis: Basis = Basis.IDENTITY


func _ready() -> void:
	Input.set_mouse_mode(Input.MOUSE_MODE_CAPTURED)
	current_protag_wanted = 1


func _input(event: InputEvent) -> void:
	input_dir = Input.get_vector("left", "right", "forward", "backward").normalized()
	if Input.get_mouse_mode() == Input.MOUSE_MODE_CAPTURED and Input.is_action_just_pressed("ui_cancel"):
		Input.set_mouse_mode(Input.MOUSE_MODE_VISIBLE)
	if Input.get_mouse_mode() == Input.MOUSE_MODE_VISIBLE and event is InputEventMouseButton:
		Input.set_mouse_mode(Input.MOUSE_MODE_CAPTURED)
	if event is InputEventMouseMotion and Input.get_mouse_mode() == Input.MOUSE_MODE_CAPTURED:
		yaw_mag = -event.relative.x
		pitch_mag = -event.relative.y



func _process(delta: float) -> void:
	pass
