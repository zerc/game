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

var Avatars = map[string]string{
	"panda":   "Panda",
	"penguin": "Penguin",
	"duck":    "Duck",
	"chicken": "Chicken",
	"koala":   "Koala",
	"rabbit":  "Rabbit",
	"zombie":  "Zombie",
	"ghost":   "Ghost",
	"alien":   "Alien",
	"robot":   "Robot",
}

func GetAvatarChoices() []string {
	result := make([]string, 0)
	for key, _ := range Avatars {
		result = append(result, key)
	}
	return result
}
