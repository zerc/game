package models

type Player struct {
	Name     string
	Colour   string
	Position *Position
}

func (p Player) ID() string {
	return p.Name
}
