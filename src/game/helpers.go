package main

import "game/models"

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

	return &models.Scene{Width: width, Height: height, Matrix: matrix}
}
