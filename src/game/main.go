package main

import (
	"flag"
	"fmt"
	"game/environments"
	"game/models"
	"log"
	"os"
	"strings"
)

// CLI flags
// Either one of these should be defined.
var serverHost = flag.String("s", "", "IP address to create a server on. Example: 127.0.0.1")
var clientHost = flag.String("c", "", "IP address of the server to connect to. Example: 127.0.0.1")

// Optional flags
var playerName = flag.String("n", "Player", "Your name")
var isBot = flag.Bool("b", false, "Current player is a bot")
var avatar = flag.String("a", "panda", fmt.Sprintf("Select your avatar. Choices are:\n\t%s", strings.Join(models.GetAvatarChoices(), ", ")))
var environment = flag.String("e", "terminal", "Select an environment to run the game: terminal or opengl")

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

	if *environment == "terminal" {
		environments.InitTerminal(isServer, host, *avatar, *playerName, *isBot)
	} else if *environment == "opengl" {
		environments.InitOpenGL(isServer, host, *avatar, *playerName, *isBot)
	} else {
		panic(fmt.Errorf("Environment %v is not supported", *environment))
	}
}
