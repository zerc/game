package main

import (
	"fmt"
	"game/models"
	"log"
	"net"
	"strconv"
	"strings"
	"time"
)

// Creates an empty scene
func CreateScene(width int, height int) *models.Scene {
	matrix := [][]*models.GameObject{}

	for i := 0; i < height; i++ {
		tmp := make([]*models.GameObject, width)

		for x, _ := range tmp {
			tmp[x] = nil
		}

		matrix = append(matrix, tmp)
	}

	return &models.Scene{Width: width, Height: height, Matrix: matrix, Index: make(map[string]*models.Player)}
}

// Inits a server
func InitServer(scene *models.Scene, port string) {
	ln, err := net.Listen("tcp", port)

	if err != nil {
		log.Fatal(err)
	}

	defer ln.Close()

	// TODO: use logging instead
	fmt.Printf("Waiting for TCP connections to 127.0.0.1:%s", port)

	for {
		conn, err := ln.Accept()

		if err != nil {
			log.Fatal(err)
		}
		fmt.Println(">> New connection")
		go AddNewPlayer(conn, scene)
	}
}

func InitServerTwo(scene *models.Scene) {
	ln, err := net.Listen("tcp", ":8089")

	if err != nil {
		log.Fatal(err)
	}

	defer ln.Close()

	for {
		conn, err := ln.Accept()

		if err != nil {
			log.Fatal(err)
		}

		go func(conn net.Conn, scene *models.Scene) {
			defer conn.Close()

			for {
				for _, player := range scene.Index {
					if player.Position != nil {
						fmt.Fprintf(conn, player.GetPositionString())
					}
				}
				time.Sleep(100 * time.Millisecond)
			}
		}(conn, scene)
	}
}

// Adds new network player to the scene
func AddNewPlayer(conn net.Conn, scene *models.Scene) {
	var player *models.Player
	defer func() {
		conn.Close()
		player.Remove()
	}()

	for {
		var tmp []byte
		n, err := fmt.Fscan(conn, &tmp)

		if err != nil {
			return
		}

		if n == 0 {
			time.Sleep(100 * time.Millisecond)
		} else {
			chunks := strings.Split(fmt.Sprintf("%s", tmp), ",")

			if len(chunks) != 4 {
				continue
			}

			id, colour := chunks[0], chunks[1]
			x, _ := strconv.Atoi(chunks[2])
			y, _ := strconv.Atoi(chunks[3])

			if scene.Index[id] == nil {
				player = &models.Player{Name: id, Colour: colour, Scene: scene}
			} else {
				player = scene.Index[id]
			}
			player.Move(x, y)
		}
	}
}

// InitClient connects to the server specified and registers the user specified.
func InitClient(player *models.Player, host *string, port *string) *net.Conn {
	fmt.Printf("Connecting to %s ...", *host)

	conn, err := net.Dial("tcp", fmt.Sprintf("%s:%s", *host, *port))
	if err != nil {
		log.Fatal(err)
	}

	fmt.Printf("Connected")
	fmt.Fprintf(conn, player.GetPositionString())
	return &conn
}
