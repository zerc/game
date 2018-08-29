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

	inputs.BindKeyboardInput(&player)

	// go func() {
	// 	ln, err := net.Listen("tcp", ":8088")

	// 	if err != nil {
	// 		log.Fatal(err)
	// 	}

	// 	defer ln.Close()

	// 	fmt.Println("Waiting for TCP connections to 127.0.0.1:8088")

	// 	for {
	// 		conn, err := ln.Accept()

	// 		if err != nil {
	// 			log.Fatal(err)
	// 		}
	// 		fmt.Println(">> New connection")
	// 		go handleConnection(conn, &scene)
	// 	}
	// }()

}

// func handleConnection(conn net.Conn, scene *Scene) {
// 	var player Player

// 	for {
// 		var tmp []byte
// 		n, err := fmt.Fscan(conn, &tmp)

// 		if err != nil {
// 			log.Fatal(err)
// 		}

// 		if n == 0 {
// 			time.Sleep(100 * time.Millisecond)
// 		} else {
// 			cmd := strings.Split(fmt.Sprintf("%s", tmp), ":")

// 			if len(cmd) != 2 {
// 				continue
// 			}

// 			if cmd[0] == "init" {
// 				player = Player{Name: cmd[1], x: 2, y: 2, s: scene, Colour: "blue"}
// 				fmt.Printf("Added new player: %s", player.Name)
// 			} else if cmd[0] == "move" {
// 				coord := strings.Split(cmd[1], ",")
// 				x, _ := strconv.Atoi(coord[0])
// 				y, _ := strconv.Atoi(coord[1])

// 				player.Move(x, y)
// 				fmt.Printf("Player %s moved to %vx%v", player.Name, x, y)
// 			}
// 		}
// 	}
// }
