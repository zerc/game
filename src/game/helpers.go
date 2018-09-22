package main

import (
	"game/models"
	"time"
)

// Creates an empty scene
func CreateScene(width int, height int) *models.Scene {
	matrix := [][]*models.GameObject{}

	for i := 0; i < height; i++ {
		tmp := make([]*models.GameObject, width)

		for x, _ := range tmp {
			tmp[x] = nil
		}

		matrix = append(matrix, tmp)
	}

	return &models.Scene{Width: width, Height: height, Matrix: matrix, Index: make(map[string]*models.Player)}
}

func InitBot(player *models.Player) {
	step := 1
	x, y := 1, 1

	for {
		x += step
		if player.Move(x, y) == false {
			step *= -1
			x += step // the new position wasn't acquired
		}
		time.Sleep(500 * time.Millisecond)
	}
}
