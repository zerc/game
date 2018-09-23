package network

import (
	"fmt"
	"game/models"
	"log"
	"net"
)

func InitClient(player *models.Player, host string) {
	addr := net.JoinHostPort(host, readPort)
	log.Printf("Client is making a connection to %s", addr)

	conn, err := net.Dial("tcp", addr)
	if err != nil {
		log.Fatal(err)
	}

	log.Printf("Client is connected")
	fmt.Fprintf(conn, player.GetPositionString())

	// All the events will be dublicated to the connection associated
	// TODO: use a queue to dispatch events
	player.Conn = &conn

	initClientReader(player, host)
}

// initReader connects to the host and reads snapshots from it.
func initClientReader(player *models.Player, host string) {
	addr := net.JoinHostPort(host, sendPort)
	log.Printf("[Reader] Client is making a connection to %s", addr)

	conn, err := net.Dial("tcp", addr)
	if err != nil {
		log.Fatal(err)
	}

	log.Printf("[Reader] Client is connected")

	go addNewPlayer(player.Scene, conn)
}
