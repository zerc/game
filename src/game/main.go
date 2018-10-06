package main

import (
	"flag"
	"fmt"
	"game/inputs"
	"game/models"
	"game/network"
	"game/renderers"
	"log"
	"os"
	"strings"

	termbox "github.com/nsf/termbox-go"
)

// CLI flags
// Either one of these should be defined.
var serverHost = flag.String("s", "", "IP address to create a server on. Example: 127.0.0.1")
var clientHost = flag.String("c", "", "IP address of the server to connect to. Example: 127.0.0.1")

// Optional flags
var playerName = flag.String("n", "Player", "Your name")
var isBot = flag.Bool("b", false, "Current player is a bot")
var avatar = flag.String("a", "panda", fmt.Sprintf("Select your avatar. Choices are:\n\t%s", strings.Join(models.GetAvatarChoices(), ", ")))

func init() {
	// Setup the logger
	log.SetFlags(log.Ldate | log.Ltime | log.Lshortfile)
	filename := "debug.txt"

	logfile, err := os.OpenFile(filename, os.O_RDWR|os.O_CREATE|os.O_APPEND, 0644)
	if err != nil {
		panic(err)
	}
	log.SetOutput(logfile)
}

func main() {
	var (
		isServer bool
		host     string
	)

	// Parse and validate CLI flags.
	flag.Parse()
	if *serverHost != "" {
		isServer = true
		host = *serverHost
	} else if *clientHost != "" {
		isServer = false
		host = *clientHost
	} else {
		panic(fmt.Errorf("either '-s' or '-c' options should be provided"))
	}
	if models.Avatars[*avatar] == "" {
		panic(fmt.Errorf("Invalid avatar selected. Use -h to see available choices"))
	}

	if err := termbox.Init(); err != nil {
		panic(err)
	}

	scene := CreateScene(20, 5)
	player := models.Player{Name: *playerName, Avatar: (*avatar), Scene: scene, Conn: nil}
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

	if *isBot {
		InitBot(&player)
	} else {
		inputs.BindKeyboardInput(&player)
	}
}
