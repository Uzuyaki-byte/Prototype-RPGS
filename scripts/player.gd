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
		
		# Check for vehicle interaction
		if Input.is_action_just_pressed("interact"):
			try_enter_nearby_vehicle()
	
	if direction != Vector3.ZERO:
		velocity.x = lerp(velocity.x, direction.x * walk_vel, 0.1)
		velocity.z = lerp(velocity.z, direction.z * walk_vel, 0.1)
	else:
		velocity.x = lerp(velocity.x, 0.0, 0.1)
		velocity.z = lerp(velocity.z, 0.0, 0.1)
	
	move_and_slide()


func try_enter_nearby_vehicle() -> void:
	# Find nearby vehicles
	var space_state = get_world_3d().direct_space_state
	var query = PhysicsShapeQueryParameters3D.new()
	var sphere = SphereShape3D.new()
	sphere.radius = 3.0
	query.shape = sphere
	query.transform = global_transform
	query.collision_mask = 0xFFFFFFFF
	
	var results = space_state.intersect_shape(query)
	for result in results:
		var collider = result.collider
		if collider.has_method("try_enter_nearest_player"):
			collider.enter_vehicle(self)
			break

