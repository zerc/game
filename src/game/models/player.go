package models

import (
	"fmt"
	"log"
	"net"
)

type Player struct {
	Name     string
	Colour   string
	Scene    *Scene
	Position *Position
	Conn     *net.Conn
}

func (p Player) ID() string {
	return p.Name
}

func (p *Player) Move(x, y int) {
	newPosition := Position{x, y}

	if ok := p.Scene.Set(p, &newPosition); ok { // The new cell is occupied successfully.
		if p.Position != nil {
			p.Scene.UnSet(p, p.Position) // Remove the player from the previous cell if there was any.
		}
		p.Position = &newPosition

		// If there is an active connection - send the data to it.
		if p.Conn != nil {
			_, err := fmt.Fprintf(*p.Conn, fmt.Sprintf("move:%d,%d\n", p.Position.x, p.Position.y))

			if err != nil {
				log.Fatal(err)
			}
		}
	}
}

func (p *Player) Left() {
	p.Move(p.Position.x-1, p.Position.y)
}

func (p *Player) Right() {
	p.Move(p.Position.x+1, p.Position.y)
}

func (p *Player) Up() {
	p.Move(p.Position.x, p.Position.y-1)
}

func (p *Player) Down() {
	p.Move(p.Position.x, p.Position.y+1)
}

func (p *Player) Remove() {
	p.Scene.UnSet(p, p.Position)
}
