package renderers

type Renderer interface {
	Draw() error     // Renders the scene.
	DrawText() error // Renders the text to the user.
}
