extends CharacterBody2D

@export var max_speed: float = 600.0
@export var acceleration: float = 400.0
@export var steering_speed: float = 3.0
@export var friction: float = 200.0
@export var brake_force: float = 800.0

var is_occupied: bool = false
var driver: CharacterBody2D = null
var enter_cooldown: float = 0.0  # Cooldown to prevent immediate exit
var current_speed: float = 0.0

@onready var driver_seat: Node2D = $DriverSeat
@onready var exit_point: Node2D = $ExitPoint
@onready var interaction_area: Area2D = $InteractionArea


func _ready() -> void:
	interaction_area.body_entered.connect(_on_body_entered)
	interaction_area.body_exited.connect(_on_body_exited)


func _physics_process(delta: float) -> void:
	# Decrease cooldown
	if enter_cooldown > 0:
		enter_cooldown -= delta
	
	if is_occupied:
		# Steering (rotates vehicle while moving)
		var steer_input = Input.get_axis("left", "right")
		if current_speed != 0.0:
			rotate(steer_input * steering_speed * delta * sign(current_speed))
		
		# Acceleration and Reversing
		var accel_input = Input.get_axis("backward", "forward")
		if accel_input != 0.0:
			current_speed = move_toward(current_speed, accel_input * max_speed, acceleration * delta)
		else:
			current_speed = move_toward(current_speed, 0.0, friction * delta)
		
		# Braking
		if Input.is_action_pressed("jump"):
			current_speed = move_toward(current_speed, 0.0, brake_force * delta)
		
		# Apply movement vector based on top-down rotation
		velocity = Vector2.UP.rotated(rotation) * current_speed
		move_and_slide()
		
		# Exit vehicle (only if cooldown expired)
		if Input.is_action_just_pressed("interact") and enter_cooldown <= 0:
			exit_vehicle()
	else:
		# Friction coast to stop when empty
		current_speed = move_toward(current_speed, 0.0, friction * delta)
		velocity = Vector2.UP.rotated(rotation) * current_speed
		move_and_slide()


func enter_vehicle(character: CharacterBody2D) -> void:
	if is_occupied:
		return
	
	driver = character
	is_occupied = true
	enter_cooldown = 0.5  # Half second cooldown before can exit
	driver.visible = false
	driver.set_physics_process(false)
	driver.set_process(false)
	driver.global_position = driver_seat.global_position
	
	# Notify camera to follow car
	PMS.set("current_vehicle", self)


func exit_vehicle() -> void:
	if not is_occupied or driver == null:
		return
	
	is_occupied = false
	driver.global_position = exit_point.global_position
	driver.visible = true
	driver.set_physics_process(true)
	driver.set_process(true)
	driver.velocity = Vector2.ZERO
	
	# Notify camera to follow player again
	PMS.set("current_vehicle", null)
	driver = null


var nearby_players: Array[CharacterBody2D] = []


func _on_body_entered(body: Node2D) -> void:
	if body is CharacterBody2D and body.has_method("_physics_process"):
		if not nearby_players.has(body):
			nearby_players.append(body)


func _on_body_exited(body: Node2D) -> void:
	if body is CharacterBody2D:
		nearby_players.erase(body)


func try_enter_nearest_player() -> bool:
	for player in nearby_players:
		if player.visible and ((player.protag_index == PMS.active_protag_index) if player.get("protag_index") else true):
			enter_vehicle(player)
			return true
	return false
