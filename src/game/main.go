package main

import (
	"flag"
	"fmt"
	"game/inputs"
	"game/models"
	"game/renderers"
)

var host = flag.String("h", "", "To connect to. For example: 127.0.0.1")
var port = flag.String("p", "8088", "Port to connect to")
var name = flag.String("n", "Player", "Your name")

func main() {
	flag.Parse()

	IsServer := true
	if *host != "" {
		IsServer = false
	}

	scene := CreateScene(20, 5)
	player := models.Player{Name: *name, Colour: "red", Scene: scene, Conn: nil}

	if IsServer == false {
		player.Colour = "blue"
	}

	player.Move(1, 1)

	renderer := renderers.Console{}
	defer renderer.DrawText("Thanks for playing the game!")
	go renderer.Start(scene)

	if IsServer {
		go InitServer(scene, fmt.Sprintf(":%s", *port))
	} else {
		go InitClient(&player, host, port)
		player.Conn = InitClient(&player, host, port)
		defer (*player.Conn).Close()
	}

	inputs.BindKeyboardInput(&player)
}
