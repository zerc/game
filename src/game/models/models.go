package models

// Describes 2D scene.
type Scene struct {
	Width  int
	Height int
	Matrix [][]GameObject
}

// Describes a position of an object on the 2D scene.
type Position struct {
	x int
	y int
}

// Anything what can placed to the scene.
type GameObject interface {
	ID() string
}

type Brick struct {
}

func (t Brick) ID() string {
	return "brick"
}

// func (p *Player) Move(x int, y int) {
// 	if !p.s.Remove(p.x, p.y, p.Name) {
// 		return
// 	}

// 	if x >= 0 && x < p.s.Width {
// 		p.x = x
// 	}

// 	if y >= 0 && y < p.s.Height {
// 		p.y = y
// 	}

// 	p.s.Add(p, p.x, p.y)
// }

// func (p *Player) Left() {
// 	p.Move(p.x-1, p.y)
// }

// func (p *Player) Right() {
// 	p.Move(p.x+1, p.y)
// }

// func (p *Player) Up() {
// 	p.Move(p.x, p.y-1)
// }

// func (p *Player) Down() {
// 	p.Move(p.x, p.y+1)
// }

// func (s *Scene) Add(p *Player, x int, y int) {

// 	if s.Matrix[y][x].ID() == "brick" {
// 		s.Matrix[y][x] = p
// 	}
// }

// func (s *Scene) Remove(x int, y int, name string) bool {

// 	if s.Matrix[y][x].ID() == name {
// 		terrain := Terrain{}
// 		s.Matrix[y][x] = &terrain
// 		return true
// 	} else if s.Matrix[y][x].ID() == "brick" {
// 		return true
// 	} else {
// 		return false
// 	}
// }
