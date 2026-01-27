extends CanvasLayer

@onready var console_panel: Panel = $ConsolePanel
@onready var input_field: LineEdit = $ConsolePanel/VBoxContainer/InputField
@onready var output_label: RichTextLabel = $ConsolePanel/VBoxContainer/OutputLabel

var is_open: bool = false
var command_history: Array[String] = []
var history_index: int = 0

const CAR_SCENE = preload("res://scenes/car.tscn")


func _ready() -> void:
	console_panel.visible = false
	input_field.text_submitted.connect(_on_command_submitted)


func _input(event: InputEvent) -> void:
	if event is InputEventKey and event.pressed:
		if event.keycode == KEY_QUOTELEFT or event.physical_keycode == KEY_QUOTELEFT:  # ~ key
			toggle_console()
			get_viewport().set_input_as_handled()
		elif is_open:
			if event.keycode == KEY_UP and command_history.size() > 0:
				history_index = max(0, history_index - 1)
				input_field.text = command_history[history_index]
				input_field.caret_column = input_field.text.length()
			elif event.keycode == KEY_DOWN and command_history.size() > 0:
				history_index = min(command_history.size(), history_index + 1)
				if history_index < command_history.size():
					input_field.text = command_history[history_index]
				else:
					input_field.text = ""
				input_field.caret_column = input_field.text.length()


func toggle_console() -> void:
	is_open = !is_open
	console_panel.visible = is_open
	
	if is_open:
		Input.set_mouse_mode(Input.MOUSE_MODE_VISIBLE)
		input_field.grab_focus()
		input_field.clear()
	else:
		Input.set_mouse_mode(Input.MOUSE_MODE_CAPTURED)


func _on_command_submitted(command: String) -> void:
	if command.strip_edges().is_empty():
		return
	
	command_history.append(command)
	history_index = command_history.size()
	
	var result = execute_command(command.strip_edges().to_lower())
	output_label.text = result + "\n" + output_label.text
	input_field.clear()


func execute_command(command: String) -> String:
	var parts = command.split(" ", false)
	if parts.size() == 0:
		return "> Invalid command"
	
	var cmd = parts[0]
	var args = parts.slice(1)
	
	match cmd:
		"car":
			return spawn_car()
		"help":
			return get_help()
		"clear":
			output_label.text = ""
			return "> Console cleared"
		_:
			return "> Unknown command: " + cmd + ". Type 'help' for available commands."


func spawn_car() -> String:
	var car_instance = CAR_SCENE.instantiate()
	
	# Spawn car near active player
	var spawn_pos = PMS.active_protag_pos + Vector3(3, 1, 0)
	car_instance.global_position = spawn_pos
	
	# Add to main scene
	get_tree().current_scene.add_child(car_instance)
	
	return "> Car spawned! Press F near it to enter."


func get_help() -> String:
	return """Available commands:
  car     - Spawn a driveable car near player
  help    - Show this help message
  clear   - Clear console output
  
Controls:
  ~       - Toggle console
  F       - Enter/exit vehicle
  WASD    - Drive
  Space   - Brake"""
