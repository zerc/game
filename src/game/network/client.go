package network

import (
	"fmt"
	"game/models"
	"log"
	"net"
)

func InitClient(player *models.Player, host string) {
	addr := net.JoinHostPort(host, readPort)
	log.Printf("[Client.Sender] making a connection to %s", addr)

	conn, err := net.Dial("tcp", addr)
	if err != nil {
		log.Fatal(err)
	}

	log.Println("[Client.Sender] connected")
	fmt.Fprintf(conn, player.GetPositionString())

	// All the events will be dublicated to the connection associated
	// TODO: use a queue to dispatch events
	player.Conn = &conn

	initClientReader(player.Scene, host)
}

// initReader connects to the host and reads snapshots from it.
func initClientReader(scene *models.Scene, host string) {
	addr := net.JoinHostPort(host, sendPort)
	log.Printf("[Client.Reader] making a connection to %s", addr)

	conn, err := net.Dial("tcp", addr)
	if err != nil {
		log.Fatal(err)
	}

	log.Println("[Client.Reader] connected")

	go addNewPlayer(scene, conn)
}
