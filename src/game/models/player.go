package models

type Player struct {
	Name     string
	Colour   string
	Position *Position
}

func (p Player) ID() string {
	return p.Name
}

// Adds the player to the scene provided.
func (p *Player) AddToScene(scene *Scene) {
	p.Position = &Position{1, 1}
	scene.Matrix[1][1] = p
}

func (p *Player) Left() {
}

func (p *Player) Right() {
}

func (p *Player) Up() {
}

func (p *Player) Down() {
}
