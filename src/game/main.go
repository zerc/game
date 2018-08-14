package main

import (
	"fmt"
	"log"
	"net"
	"strconv"
	"strings"
	"time"

	termbox "github.com/nsf/termbox-go"
)

type Scene struct {
	Width  int
	Height int
	Matrix [][]GameObject
}

type GameObject interface {
	ID() string
	Render() string
}

type Player struct {
	Name   string
	Colour string
	x      int
	y      int
	s      *Scene
}

func (p Player) Render() string {
	if p.Colour == "red" {
		return "\033[1m\033[31m░\033[0m\033[21m"
	} else if p.Colour == "blue" {
		return "\033[1m\033[34m░\033[0m\033[21m"
	} else {
		return "░"
	}
}

func (p Player) ID() string {
	return p.Name
}

func (p *Player) Move(x int, y int) {
	if !p.s.Remove(p.x, p.y, p.Name) {
		return
	}

	if x >= 0 && x < p.s.Width {
		p.x = x
	}

	if y >= 0 && y < p.s.Height {
		p.y = y
	}

	p.s.Add(p, p.x, p.y)
}

func (p *Player) Left() {
	p.Move(p.x-1, p.y)
}

func (p *Player) Right() {
	p.Move(p.x+1, p.y)
}

func (p *Player) Up() {
	p.Move(p.x, p.y-1)
}

func (p *Player) Down() {
	p.Move(p.x, p.y+1)
}

type Terrain struct {
	Name string
}

func (t Terrain) ID() string {
	return "brick"
}

func (t Terrain) Render() string {
	return " "
}

func (s *Scene) Init() {
	terrain := Terrain{}

	for i := 0; i < s.Height; i++ {
		tmp := make([]GameObject, s.Width)

		for x, _ := range tmp {
			tmp[x] = &terrain
		}

		s.Matrix = append(s.Matrix, tmp)
	}
}

func (s *Scene) Add(p *Player, x int, y int) {

	if s.Matrix[y][x].ID() == "brick" {
		s.Matrix[y][x] = p
	}
}

func (s *Scene) Remove(x int, y int, name string) bool {

	if s.Matrix[y][x].ID() == name {
		terrain := Terrain{}
		s.Matrix[y][x] = &terrain
		return true
	} else if s.Matrix[y][x].ID() == "brick" {
		return true
	} else {
		return false
	}
}

func (s *Scene) Draw() string {
	var tmp []string
	tmp = append(tmp, fmt.Sprintf("┏%s┓", strings.Repeat("━", s.Width)))

	for _, row := range s.Matrix {
		rowTmp := make([]string, s.Width+2)
		rowTmp = append(rowTmp, "┃")

		for _, column := range row {
			rowTmp = append(rowTmp, column.Render())
		}
		rowTmp = append(rowTmp, "┃")
		tmp = append(tmp, strings.Join(rowTmp, ""))
	}

	tmp = append(tmp, fmt.Sprintf("┗%s┛", strings.Repeat("━", s.Width)))
	return strings.Join(tmp, "\n")
}

func main() {
	scene := Scene{20, 5, [][]GameObject{}}
	scene.Init()

	player := Player{Name: "zero13cool", x: 0, y: 0, s: &scene, Colour: "red"}
	player.Move(1, 1)

	fmt.Println("\033[H\033[2J")
	fmt.Println(scene.Draw())

	err := termbox.Init()
	if err != nil {
		panic(err)
	}
	defer termbox.Close()

	defer func() {
		fmt.Println("\033[H\033[2J")
		fmt.Println("Bye!")
	}()

	eventQueue := make(chan termbox.Event)
	go func() {
		for {
			eventQueue <- termbox.PollEvent()
		}
	}()

	go func() {
		ln, err := net.Listen("tcp", ":8088")

		if err != nil {
			log.Fatal(err)
		}

		defer ln.Close()

		fmt.Println("Waiting for TCP connections to 127.0.0.1:8088")

		for {
			conn, err := ln.Accept()

			if err != nil {
				log.Fatal(err)
			}
			fmt.Println(">> New connection")
			go handleConnection(conn, &scene)
		}
	}()

	for {
		select {
		case event := <-eventQueue:
			if event.Type == termbox.EventKey {
				switch {
				case event.Key == termbox.KeyArrowLeft || event.Ch == 'h':
					player.Left()
				case event.Key == termbox.KeyArrowRight || event.Ch == 'l':
					player.Right()
				case event.Key == termbox.KeyArrowUp || event.Ch == 'k':
					player.Up()
				case event.Key == termbox.KeyArrowDown || event.Ch == 'j':
					player.Down()
				case event.Ch == 'q' || event.Key == termbox.KeyEsc || event.Key == termbox.KeyCtrlC || event.Key == termbox.KeyCtrlD:
					return
				}
			}
		default:
			time.Sleep(100 * time.Millisecond)
			fmt.Println("\033[H\033[2J")
			fmt.Println(scene.Draw())
		}
	}
}

func handleConnection(conn net.Conn, scene *Scene) {
	var player Player

	for {
		var tmp []byte
		n, err := fmt.Fscan(conn, &tmp)

		if err != nil {
			log.Fatal(err)
		}

		if n == 0 {
			time.Sleep(100 * time.Millisecond)
		} else {
			cmd := strings.Split(fmt.Sprintf("%s", tmp), ":")

			if len(cmd) != 2 {
				continue
			}

			if cmd[0] == "init" {
				player = Player{Name: cmd[1], x: 2, y: 2, s: scene, Colour: "blue"}
				fmt.Printf("Added new player: %s", player.Name)
			} else if cmd[0] == "move" {
				coord := strings.Split(cmd[1], ",")
				x, _ := strconv.Atoi(coord[0])
				y, _ := strconv.Atoi(coord[1])

				player.Move(x, y)
				fmt.Printf("Player %s moved to %vx%v", player.Name, x, y)
			}
		}
	}
}
