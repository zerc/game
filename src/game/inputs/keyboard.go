package inputs

import (
	"fmt"
	"game/models"

	termbox "github.com/nsf/termbox-go"
)

// Binds input from the keyboard to the player given.
func BindKeyboardInput(p *models.Player) {
	if !termbox.IsInit {
		panic(fmt.Errorf("Termbox isn't initialised!"))
	}

	eventQueue := make(chan termbox.Event)
	go func() {
		for {
			eventQueue <- termbox.PollEvent()
		}
	}()

	for {
		select {
		case event := <-eventQueue:
			if event.Type == termbox.EventKey {
				switch {
				case event.Key == termbox.KeyArrowLeft || event.Ch == 'h':
					p.Left()
				case event.Key == termbox.KeyArrowRight || event.Ch == 'l':
					p.Right()
				case event.Key == termbox.KeyArrowUp || event.Ch == 'k':
					p.Up()
				case event.Key == termbox.KeyArrowDown || event.Ch == 'j':
					p.Down()
				case event.Ch == 'q' || event.Key == termbox.KeyEsc || event.Key == termbox.KeyCtrlC || event.Key == termbox.KeyCtrlD:
					return
				}
			}
		}
	}
}
