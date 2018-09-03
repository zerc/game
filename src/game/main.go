package main

import (
	"game/inputs"
	"game/models"
	"game/renderers"
)

func main() {
	scene := CreateScene(20, 5)

	player := models.Player{Name: "zero13cool", Colour: "red", Scene: scene}
	player.Move(1, 1)

	renderer := renderers.Console{}
	defer renderer.DrawText("Thanks for playing the game!")
	go renderer.Start(scene)
	go InitServer(scene, ":8088")

	inputs.BindKeyboardInput(&player)
}
