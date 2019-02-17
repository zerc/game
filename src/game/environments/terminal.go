package environments

import (
	"fmt"
	"game/inputs"
	"game/models"
	"game/network"
	"game/renderers"
	"log"

	termbox "github.com/nsf/termbox-go"
)

// InitTerminal inits the game as in-termnial application.
func InitTerminal(isServer bool, host string, avatar string, name string, isBot bool) {
	if err := termbox.Init(); err != nil {
		panic(err)
	}

	scene := CreateScene(20, 5)
	player := models.Player{Name: name, Avatar: (avatar), Scene: scene, Conn: nil}
	player.Move(1, 1)
	log.SetPrefix(fmt.Sprintf("[%s] ", player.ID()))

	renderer := renderers.Console{}
	go renderer.Start(scene)

	// Register cleanup actions
	defer func(player *models.Player) {
		termbox.Close()
		renderer.DrawText("Thanks for playing the game!")

		if player.Conn != nil {
			(*player.Conn).Close()
		}
	}(&player)

	if isServer {
		network.InitServer(scene, host)
	} else {
		network.InitClient(&player, host)
	}

	if isBot {
		InitBot(&player)
	} else {
		inputs.BindKeyboardInput(&player)
	}
}
