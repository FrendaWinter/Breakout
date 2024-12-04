extends Node

@onready var brickObject = preload("res://Scenes/brick.tscn")
@onready var heartObject = preload("res://Scenes/heart.tscn")

var columns = 13
var rows = 3
var margin = 50

# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	setupLevel()

func setupLevel():
	for r in rows:
		for c in columns:
			var randomNumber = randi_range(0, 2)
			if randomNumber > 0:
				var newBrick = brickObject.instantiate()
				add_child(newBrick)
				newBrick.position = Vector2(margin + 80 * c, 48 + margin +  80 * r)
	for i in range(3):
		var newHeart = heartObject.instantiate()
		add_child(newHeart)
		newHeart.position = Vector2(margin + 80 * i, 48)

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta: float) -> void:
	pass
