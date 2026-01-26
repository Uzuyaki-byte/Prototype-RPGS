extends Node

@export var input_dir: Vector2 = Vector2.ZERO
@export var mouse_sens: float = 1
@export var active_protag_pos: Vector3
@export var active_protag_index: int
@export var protag_1_pos: Vector3
@export var protag_2_pos: Vector3
@export var looking_basis: Basis = Basis.IDENTITY


func _ready() -> void:
	Input.set_mouse_mode(Input.MOUSE_MODE_CAPTURED)
	active_protag_index = 1


func _input(event: InputEvent) -> void:
	input_dir = Input.get_vector("left", "right", "forward", "backward").normalized()
	if Input.is_action_just_pressed("switch_character"):
		if active_protag_index == 1:
			active_protag_index = 2
		elif active_protag_index == 2:
			active_protag_index = 1
	if Input.get_mouse_mode() == Input.MOUSE_MODE_CAPTURED and Input.is_action_just_pressed("ui_cancel"):
		Input.set_mouse_mode(Input.MOUSE_MODE_VISIBLE)
	if Input.get_mouse_mode() == Input.MOUSE_MODE_VISIBLE and event is InputEventMouseButton:
		Input.set_mouse_mode(Input.MOUSE_MODE_CAPTURED)


func _process(delta: float) -> void:
	match active_protag_index:
		1:
			active_protag_pos = protag_1_pos
		2:
			active_protag_pos = protag_2_pos
	print(active_protag_index)
