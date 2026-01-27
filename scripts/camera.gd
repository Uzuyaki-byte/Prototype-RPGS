extends Node3D

@onready var spring_arm: SpringArm3D = $yaw/pitch/SpringArm3D
@onready var camera: Node3D = $"."
@onready var yaw: Node3D = $yaw
@onready var pitch: Node3D = $yaw/pitch
var yaw_mag: float
var pitch_mag: float


func _ready() -> void:
	pass


func _input(event: InputEvent) -> void:
	if event is InputEventMouseMotion and Input.get_mouse_mode() == Input.MOUSE_MODE_CAPTURED:
		yaw_mag += -event.relative.x
		pitch_mag += -event.relative.y


func _physics_process(delta: float) -> void:
	# Follow vehicle if player is in one, otherwise follow active player
	if PMS.current_vehicle != null:
		self.global_position = PMS.current_vehicle.global_position + Vector3(0, 1.5, 0)
	else:
		self.global_position = PMS.active_protag_pos
	yaw.rotate_y(yaw_mag * delta * PMS.mouse_sens)
	pitch.rotate_x(pitch_mag * delta * PMS.mouse_sens)
	pitch.rotation.x = clamp(pitch.rotation.x, deg_to_rad(-90), deg_to_rad(120) )
	PMS.looking_basis = yaw.global_transform.basis
	yaw_mag = lerp(yaw_mag,0.0, 0.2)
	pitch_mag = lerp(pitch_mag, 0.0, 0.2)

