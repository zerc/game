package renderers

type Renderer interface {
	Start()          // Renders the scene in inifite loop.
	Draw() error     // Renders the scene.
	DrawText() error // Renders the text to the user.
}
