package models

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
