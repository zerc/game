package models

import (
	"fmt"
	"log"
	"net"
)

type Player struct {
	Name     string
	Color    string
	Scene    *Scene
	Position *Position
	Conn     *net.Conn
}

func (p Player) ID() string {
	return p.Name
}

func (p *Player) Move(x, y int) bool {
	newPosition := Position{x, y}

	if p.Scene.Index[p.ID()] == nil {
		p.Scene.Index[p.ID()] = p
	}

	if ok := p.Scene.Set(p, &newPosition); ok { // The new cell is occupied successfully.
		if p.Position != nil {
			p.Scene.UnSet(p, p.Position) // Remove the player from the previous cell if there was any.
		}
		p.Position = &newPosition

		// If there is an active connection - send the data to it.
		if p.Conn != nil {
			_, err := fmt.Fprintf(*p.Conn, p.GetPositionString())

			if err != nil {
				log.Fatal(err)
			}
		}

		return true
	}

	return false
}

func (p *Player) GetPositionString() string {
	if p.Position != nil {
		return fmt.Sprintf("%s,%s,%d,%d\n", p.ID(), p.Color, p.Position.x, p.Position.y)
	}

	return ""
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
