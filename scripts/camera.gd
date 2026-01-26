extends Node3D

@onready var spring_arm: SpringArm3D = $yaw/pitch/SpringArm3D
@onready var camera: Node3D = $"."
@onready var yaw: Node3D = $yaw
@onready var pitch: Node3D = $yaw/pitch


func _ready() -> void:
	pass


func _process(delta: float) -> void:
	spring_arm.global_position = PMS.protag_1_pos
	yaw.rotate_y(PMS.yaw_mag * delta * PMS.mouse_sens)
	pitch.rotate_x(PMS.pitch_mag * delta * PMS.mouse_sens)
	pitch.rotation.x = clamp(pitch.rotation.x, deg_to_rad(-90), deg_to_rad(120) )
	PMS.looking_basis = yaw.global_transform.basis
	PMS.yaw_mag = 0
	PMS.pitch_mag = 0
