package environments

import (
	"fmt"
	"game/models"
	"image"
	"image/draw"
	_ "image/jpeg"
	"os"
	"strings"
	"time"

	"github.com/go-gl/gl/v4.1-core/gl"
)

// CreateScene creates an empty scene
func CreateScene(width int, height int) *models.Scene {
	matrix := [][]*models.GameObject{}

	for i := 0; i < height; i++ {
		tmp := make([]*models.GameObject, width)

		for x := range tmp {
			tmp[x] = nil
		}

		matrix = append(matrix, tmp)
	}

	return &models.Scene{Width: width, Height: height, Matrix: matrix, Index: make(map[string]*models.Player)}
}

// InitBot initiates simple bot which emulates another player
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

// CompileShader compiles shader from the source given.
func CompileShader(source string, shaderType uint32) (uint32, error) {
	shader := gl.CreateShader(shaderType)

	csources, free := gl.Strs(source)
	gl.ShaderSource(shader, 1, csources, nil)
	free()
	gl.CompileShader(shader)

	var status int32
	gl.GetShaderiv(shader, gl.COMPILE_STATUS, &status)
	if status == gl.FALSE {
		var logLen int32
		gl.GetShaderiv(shader, gl.INFO_LOG_LENGTH, &logLen)

		log := strings.Repeat("\x00", int(logLen+1))
		gl.GetShaderInfoLog(shader, logLen, nil, gl.Str(log))

		return 0, fmt.Errorf("failed to compile %v: %v", source, log)
	}

	return shader, nil
}

// LoadTexture loads texture specified.
func LoadTexture(filename string) (uint32, error) {
	f, err := os.Open(filename)
	if err != nil {
		return 0, fmt.Errorf("Can't load texture %q error: %v", filename, err)
	}

	img, _, err := image.Decode(f)
	if err != nil {
		return 0, err
	}

	rgba := image.NewRGBA(img.Bounds())
	if rgba.Stride != rgba.Rect.Size().X*4 {
		return 0, fmt.Errorf("unsupported stride") // TODO: what is this?
	}

	draw.Draw(rgba, rgba.Bounds(), img, image.Point{0, 0}, draw.Src)

	var texture uint32
	gl.GenTextures(1, &texture)
	gl.ActiveTexture(gl.TEXTURE0)
	gl.BindTexture(gl.TEXTURE_2D, texture)
	gl.TexParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.LINEAR)
	gl.TexParameteri(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.LINEAR)
	gl.TexParameteri(gl.TEXTURE_2D, gl.TEXTURE_WRAP_S, gl.CLAMP_TO_EDGE)
	gl.TexParameteri(gl.TEXTURE_2D, gl.TEXTURE_WRAP_T, gl.CLAMP_TO_EDGE)
	gl.TexImage2D(
		gl.TEXTURE_2D,
		0,
		gl.RGBA,
		int32(rgba.Rect.Size().X),
		int32(rgba.Rect.Size().Y),
		0,
		gl.RGBA,
		gl.UNSIGNED_BYTE,
		gl.Ptr(rgba.Pix))

	return texture, nil
}
