package renderers

import (
	"fmt"
	"game/models"
	"time"

	termbox "github.com/nsf/termbox-go"
)

// AvatarsToIcon is a map from code to unicode representation
var AvatarsToIcon = map[string]rune{
	"panda":   '🐼',
	"penguin": '🐧',
	"zombie":  '🧟',
	"ghost":   '👻',
	"alien":   '👾',
	"robot":   '🤖',
}

// Console renders everything to the terminal's stdout.
type Console struct {
}

// DrawText draws a text provided.
func (c Console) DrawText(s string) error {
	fmt.Println("\033[H\033[2J")
	fmt.Println(s)
	return nil
}

// Start starts rendering the scene in the infinite loop.
func (c Console) Start(s *models.Scene) {
	for {
		c.Draw(s)
		time.Sleep(10 * time.Millisecond)
	}
}

// Draw draws the whole 2D scene.
func (c Console) Draw(s *models.Scene) error {
	var r rune

	// Top border
	for i := 0; i <= s.Width+1; i++ {
		switch {
		case i == 0:
			r = '┏'
		case i > s.Width:
			r = '┓'
		default:
			r = '━'
		}
		termbox.SetCell(i+1, 1, r, termbox.ColorWhite, termbox.ColorDefault)
	}

	// Body
	for y, row := range s.Matrix {
		termbox.SetCell(1, y+2, '┃', termbox.ColorWhite, termbox.ColorDefault)

		for x, obj := range row {
			cell := Render(obj)
			termbox.SetCell(x+2, y+2, cell.Ch, cell.Fg, cell.Bg)
		}

		termbox.SetCell(s.Width+2, y+2, '┃', termbox.ColorWhite, termbox.ColorDefault)
	}

	// Bottom border
	for i := 0; i <= s.Width+1; i++ {
		switch {
		case i == 0:
			r = '┗'
		case i > s.Width:
			r = '┛'
		default:
			r = '━'
		}
		termbox.SetCell(i+1, s.Height+2, r, termbox.ColorWhite, termbox.ColorDefault)
	}

	termbox.Flush()

	return nil
}

// Render renders a game object specified
func Render(o *models.GameObject) termbox.Cell {
	emptyCell := termbox.Cell{Ch: ' ', Fg: termbox.ColorDefault, Bg: termbox.ColorDefault}
	if o == nil {
		return emptyCell
	} else if p, ok := (*o).(*models.Player); ok {
		cell := termbox.Cell{Ch: AvatarsToIcon[p.Avatar], Fg: termbox.ColorDefault, Bg: termbox.ColorDefault}
		return cell
	} else {
		return emptyCell
	}
}
