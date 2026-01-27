extends CharacterBody3D

@onready var shape_cast_3d: ShapeCast3D = $ShapeCast3D
var protag_index: int = 1
var jump_imp: float = 10.0
var walk_vel: float = 9.0
var gravity: float = 20.0
var direction: Vector3 = Vector3.ZERO


func _process(delta: float) -> void:
	PMS.protag_1_pos = shape_cast_3d.global_position


func _physics_process(delta: float) -> void:
	if protag_index == PMS.active_protag_index:
		if Input.is_action_just_pressed("jump") and is_on_floor():
			velocity.y = jump_imp
		
		if not is_on_floor():
			velocity.y -= gravity * delta
		
		direction = PMS.looking_basis * Vector3(PMS.input_dir.x, 0.0, PMS.input_dir.y)
	
	if direction != Vector3.ZERO:
		velocity.x = lerp(velocity.x, direction.x * walk_vel, 0.1)
		velocity.z = lerp(velocity.z, direction.z * walk_vel, 0.1)
	else:
		velocity.x = lerp(velocity.x, 0.0, 0.1)
		velocity.z = lerp(velocity.z, 0.0, 0.1)
	
	move_and_slide()
