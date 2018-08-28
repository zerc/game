package models

import "fmt"

// Describes 2D scene.
type Scene struct {
	Width  int
	Height int
	Matrix [][]*GameObject
}

// Extracts a game object from the position given.
// Returns error if the position is invalid e.g. null or exceeds the scene's size.
func (s *Scene) Get(pos *Position) (*GameObject, error) {
	if pos == nil {
		return nil, fmt.Errorf("Can't fetch an object from empty position!")
	}

	if pos.y < 0 || pos.y >= s.Height {
		return nil, fmt.Errorf("Y is out of range %d", pos.y)
	}

	if pos.x < 0 || pos.x >= s.Width {
		return nil, fmt.Errorf("X is out of range %d", pos.x)
	}

	return s.Matrix[pos.y][pos.x], nil
}

// Sets an object to the given position.
func (s *Scene) Set(obj GameObject, pos *Position) bool {
	if currentObj, err := s.Get(pos); err == nil {
		if currentObj == nil {
			s.Matrix[pos.y][pos.x] = &obj
		} else {
			s.Matrix[pos.y][pos.x] = nil
		}
		return true
	}

	return false
}

// Removes the game object given from the position given.
// Checks that the position specified is actually occupied by the given object
// and proceed only if that is true.
func (s *Scene) UnSet(obj GameObject, pos *Position) {
	if currentObj, err := s.Get(pos); err == nil {
		if currentObj != nil && (*currentObj).ID() == obj.ID() {
			s.Set(nil, pos)
		}
	}
}
