package environments

import (
	"log"
	"runtime"

	"github.com/go-gl/gl/v4.1-core/gl"
	"github.com/go-gl/glfw/v3.2/glfw"
)

var (
	vertices = []float32{
		// positions   // texture coordinates
		0, 0.5, 0, 1, 1,
		-1, 0, 0, 0, 1,
		0, -1, 0, 0, 0,
		1, 0, 0, 1, 0,
		0, 0, 0, 0.5, 0.5,
	}

	indexes = []uint32{
		0, 1, 4, // first triangle
		1, 2, 3, // second triangle
	}

	vertexShaderSource = `
		#version 410
		layout (location = 0) in vec3 vp;
		layout (location = 1) in vec2 aTexCoord;

		out vec2 TexCoord;

		void main() {
			gl_Position = vec4(vp, 1.0);
			TexCoord = aTexCoord;
		}
	` + "\x00"

	fragmentShaderSource = `
		#version 410
		out vec4 frag_colour;

		in vec2 TexCoord;

		uniform sampler2D ourTexture;

		void main() {
			frag_colour = texture(ourTexture, TexCoord);
		}
	` + "\x00"
)

// frag_colour = vec4(0.5, 29, 120, 171);
// InitOpenGL inits the game as OpenGL application.
func InitOpenGL(isServer bool, host string, avatar string, name string, isBot bool) {
	runtime.LockOSThread()

	window := initGlfw()
	defer glfw.Terminate()

	program := _initOpenGL()

	vao := makeVao(vertices, indexes)
	texture, err := LoadTexture("static/texture_02.jpg")
	if err != nil {
		panic(err)
	}

	for !window.ShouldClose() {
		render(window, program, vao, texture)
	}
}

func _initOpenGL() uint32 {
	if err := gl.Init(); err != nil {
		panic(err)
	}

	version := gl.GoStr(gl.GetString(gl.VERSION))
	log.Printf("OpenGL version %v", version)

	vertexShader, err := CompileShader(vertexShaderSource, gl.VERTEX_SHADER)
	if err != nil {
		panic(err)
	}

	fragmentShader, err := CompileShader(fragmentShaderSource, gl.FRAGMENT_SHADER)
	if err != nil {
		panic(err)
	}

	p := gl.CreateProgram()
	gl.AttachShader(p, vertexShader)
	gl.AttachShader(p, fragmentShader)
	gl.LinkProgram(p)

	return p
}

func initGlfw() *glfw.Window {
	if err := glfw.Init(); err != nil {
		panic(err)
	}

	glfw.WindowHint(glfw.Resizable, glfw.False)
	glfw.WindowHint(glfw.ContextVersionMajor, 4)
	glfw.WindowHint(glfw.ContextVersionMinor, 1)
	glfw.WindowHint(glfw.OpenGLProfile, glfw.OpenGLCoreProfile)
	glfw.WindowHint(glfw.OpenGLForwardCompatible, glfw.True)

	window, err := glfw.CreateWindow(640, 480, "Game", nil, nil)
	if err != nil {
		panic(err)
	}

	window.MakeContextCurrent()

	return window
}

func render(window *glfw.Window, program uint32, vao uint32, texture uint32) {
	gl.Clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT)
	gl.UseProgram(program)

	gl.BindTexture(gl.TEXTURE_2D, texture)
	gl.BindVertexArray(vao)
	gl.DrawElements(gl.TRIANGLES, int32(len(indexes)), gl.UNSIGNED_INT, nil)

	window.SwapBuffers()
	glfw.PollEvents()
}

// makeVao makes vertex array from the points provided.
func makeVao(points []float32, indexes []uint32) uint32 {
	var (
		vao uint32
		vbo uint32
		ebo uint32
	)

	gl.GenVertexArrays(1, &vao)
	gl.GenBuffers(1, &vbo)
	gl.GenBuffers(1, &ebo)

	gl.BindVertexArray(vao)

	gl.BindBuffer(gl.ARRAY_BUFFER, vbo)
	gl.BufferData(gl.ARRAY_BUFFER, 4*len(points), gl.Ptr(points), gl.STATIC_DRAW)

	gl.BindBuffer(gl.ELEMENT_ARRAY_BUFFER, ebo)
	gl.BufferData(gl.ELEMENT_ARRAY_BUFFER, 4*len(indexes), gl.Ptr(indexes), gl.STATIC_DRAW)

	gl.VertexAttribPointer(0, 3, gl.FLOAT, false, 20, nil)
	gl.EnableVertexAttribArray(0)

	gl.VertexAttribPointer(1, 2, gl.FLOAT, false, 20, nil)
	gl.EnableVertexAttribArray(1)

	gl.BindBuffer(gl.ARRAY_BUFFER, 0)
	gl.BindVertexArray(0)

	return vao
}
