extends Node

@export var input_dir: Vector2 = Vector2.ZERO
@export var active_protag_pos: Vector2 = Vector2.ZERO
@export var active_protag_index: int = 1
@export var protag_1_pos: Vector2 = Vector2.ZERO
@export var protag_2_pos: Vector2 = Vector2.ZERO
@export var looking_dir: Vector2 = Vector2.DOWN
@export var current_vehicle: Node2D = null
@export var mouse_sens: float = 0.3


func _ready() -> void:
	active_protag_index = 1


func _input(event: InputEvent) -> void:
	input_dir = Input.get_vector("left", "right", "forward", "backward").normalized()
	
	if Input.is_action_just_pressed("switch_character"):
		if active_protag_index == 1:
			active_protag_index = 2
		elif active_protag_index == 2:
			active_protag_index = 1


func _physics_process(_delta: float) -> void:
	match active_protag_index:
		1:
			active_protag_pos = protag_1_pos
		2:
			active_protag_pos = protag_2_pos


func _process(_delta: float) -> void:
	match active_protag_index:
		1:
			active_protag_pos = protag_1_pos
		2:
			active_protag_pos = protag_2_pos
