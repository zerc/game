package main

import (
	"flag"
	"fmt"
	"game/inputs"
	"game/models"
	"game/renderers"
	"log"
	"net"
)

var host = flag.String("h", "", "To connect to. For example: 127.0.0.1")
var port = flag.String("p", "8088", "Port to connect to")
var name = flag.String("n", "Player", "Your name")
var colour = flag.String("c", "red", "Your colour. Choices are: red, blue, green, orange")

func main() {
	flag.Parse()

	IsServer := true
	if *host != "" {
		IsServer = false
	}

	scene := CreateScene(20, 5)
	player := models.Player{Name: *name, Colour: *colour, Scene: scene, Conn: nil}

	if IsServer {
		player.Move(1, 1)
	} else {
		player.Move(1, 2)
	}

	renderer := renderers.Console{}
	defer renderer.DrawText("Thanks for playing the game!")
	go renderer.Start(scene)

	if IsServer {
		go InitServer(scene, fmt.Sprintf(":%s", *port))
		go InitServerTwo(scene)
	} else {
		player.Conn = InitClient(&player, host, port)
		defer (*player.Conn).Close()

		go func(scene *models.Scene, host *string) {
			conn, err := net.Dial("tcp", fmt.Sprintf("%s:%s", *host, "8089"))
			if err != nil {
				log.Fatal(err)
			}

			AddNewPlayer(conn, scene)

		}(scene, host)
	}

	inputs.BindKeyboardInput(&player)
}
