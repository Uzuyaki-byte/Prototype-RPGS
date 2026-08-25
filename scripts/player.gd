extends CharacterBody2D

@onready var shape_cast_2d: ShapeCast2D = $ShapeCast2D
var protag_index: int = 1
var walk_vel: float = 300.0
var direction: Vector2 = Vector2.ZERO


func _ready() -> void:
	PMS.protag_1_pos = global_position


func _process(_delta: float) -> void:
	PMS.protag_1_pos = global_position


func _physics_process(_delta: float) -> void:
	if protag_index == PMS.active_protag_index:
		# Rotate input vector relative to the camera's looking direction
		direction = PMS.input_dir.rotated(PMS.looking_dir.angle())
		
		# Check for vehicle interaction
		if Input.is_action_just_pressed("interact"):
			try_enter_nearby_vehicle()
	else:
		direction = Vector2.ZERO
	
	if direction != Vector2.ZERO:
		velocity = velocity.lerp(direction * walk_vel, 0.1)
	else:
		velocity = velocity.lerp(Vector2.ZERO, 0.1)
	
	move_and_slide()
	PMS.protag_1_pos = global_position


func try_enter_nearby_vehicle() -> void:
	# Find nearby vehicles in 2D physics space
	var space_state = get_world_2d().direct_space_state
	var query = PhysicsShapeQueryParameters2D.new()
	var circle = CircleShape2D.new()
	circle.radius = 48.0  # Scaled up for 2D pixel space
	query.shape = circle
	query.transform = global_transform
	query.collision_mask = 0xFFFFFFFF
	
	var results = space_state.intersect_shape(query)
	for result in results:
		var collider = result.collider
		if collider.has_method("try_enter_nearest_player"):
			collider.enter_vehicle(self)
			break
