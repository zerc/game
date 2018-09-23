package network

import (
	"fmt"
	"game/models"
	"log"
	"net"
	"strconv"
	"strings"
	"time"
)

// Constants
var (
	readPort = "8088" // a port to receive data
	sendPort = "8089" // a port to send data
)

// InitServer inits a server.
// The server conists from two parts:
// 1. Receive part - each clients sends its data and the server receives it.
// 2. Send part - the server sends snapshots of the scene to all the connected clients.
func InitServer(scene *models.Scene, host string) {
	go initReader(scene, host)
	go initSender(scene, host)
}

// initReader creates a listner to accept client connections and receive data from them.
func initReader(scene *models.Scene, host string) {
	addr := net.JoinHostPort(host, readPort)

	ln, err := net.Listen("tcp", addr)
	if err != nil {
		log.Fatal(err)
	}
	defer ln.Close()
	log.Printf("[Reader] waiting for TCP connections to %s", addr)

	for {
		conn, err := ln.Accept()
		if err != nil {
			log.Fatal(err)
		}
		log.Println("[Reader] new connection")
		go addNewPlayer(scene, conn)
	}
}

// addNewPlayer adds new players to the scene.
// If the player is not in the index - it will be added.
// For existing players the position will be updated accordingly.
func addNewPlayer(scene *models.Scene, conn net.Conn) {
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

			id, avatar := chunks[0], chunks[1]
			x, _ := strconv.Atoi(chunks[2])
			y, _ := strconv.Atoi(chunks[3])

			if scene.Index[id] == nil {
				player = &models.Player{Name: id, Avatar: avatar, Scene: scene}
			} else {
				player = scene.Index[id]
			}
			player.Move(x, y)
		}
	}
}

// initSender creates a listner to accept client connections and send snapshots of the scene
// back to them.
func initSender(scene *models.Scene, host string) {
	addr := net.JoinHostPort(host, sendPort)

	ln, err := net.Listen("tcp", addr)
	if err != nil {
		log.Fatal(err)
	}
	defer ln.Close()
	log.Printf("[Sender] waiting for TCP connections to %s", addr)

	for {
		conn, err := ln.Accept()
		if err != nil {
			log.Fatal(err)
		}
		log.Println("[Sender] New connection")
		go addSubscriber(scene, conn)
	}
}

// addSubscriber registers a client as a subscriber to receive snapshots of the scene.
func addSubscriber(scene *models.Scene, conn net.Conn) {
	defer conn.Close()

	for {
		// Iterate over the scene's index and send data of every registered object.
		for _, player := range scene.Index {
			if player.Position != nil {
				fmt.Fprintf(conn, player.GetPositionString())
			}
		}
		time.Sleep(100 * time.Millisecond)
	}
}
