extends VehicleBody3D

@export var engine_force_value: float = 4000.0
@export var steering_limit: float = 0.4
@export var brake_force: float = 50.0

var is_occupied: bool = false
var driver: CharacterBody3D = null
var enter_cooldown: float = 0.0  # Cooldown to prevent immediate exit
@onready var driver_seat: Node3D = $DriverSeat
@onready var exit_point: Node3D = $ExitPoint
@onready var interaction_area: Area3D = $InteractionArea


func _ready() -> void:
	interaction_area.body_entered.connect(_on_body_entered)
	interaction_area.body_exited.connect(_on_body_exited)


func _physics_process(delta: float) -> void:
	# Decrease cooldown
	if enter_cooldown > 0:
		enter_cooldown -= delta
	
	if is_occupied:
		# Steering
		var steer_input = Input.get_axis("right", "left")
		steering = lerp(steering, steer_input * steering_limit, 5.0 * delta)
		
		# Acceleration
		var accel_input = Input.get_axis("backward", "forward")
		engine_force = accel_input * engine_force_value
		
		# Braking
		if Input.is_action_pressed("jump"):
			brake = brake_force
		else:
			brake = 0.0
		
		# Exit vehicle (only if cooldown expired)
		if Input.is_action_just_pressed("interact") and enter_cooldown <= 0:
			exit_vehicle()


func enter_vehicle(character: CharacterBody3D) -> void:
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
	driver.velocity = Vector3.ZERO
	
	# Notify camera to follow player again
	PMS.set("current_vehicle", null)
	driver = null


var nearby_players: Array[CharacterBody3D] = []


func _on_body_entered(body: Node3D) -> void:
	if body is CharacterBody3D and body.has_method("_physics_process"):
		if not nearby_players.has(body):
			nearby_players.append(body)


func _on_body_exited(body: Node3D) -> void:
	if body is CharacterBody3D:
		nearby_players.erase(body)


func try_enter_nearest_player() -> bool:
	for player in nearby_players:
		if player.visible and ((player.protag_index == PMS.active_protag_index) if player.get("protag_index") else true):
			enter_vehicle(player)
			return true
	return false
