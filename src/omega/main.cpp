#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include "o_math.hpp"

const float init_width    = 640;
const float init_height   = 480;
const float fov    = 1;  // tan(90/2) i.e. FOV is 90 degree

/*
Logic:

1. Cast rays: from origin (0, 0, 0) to center of each pixel from the framebuffer.
2. For each ray need to check either it intersects with the Sphere or not
3. Render: based on [2] draw pixels differently

Objects:

    Vector - just to work with (x, y, z)
    Sphere - to represent an object (center, radius)
    Light - to represent a source of light

TODO:
    * refactor the code, do not create the vertex array on every iteration, remove the implementation from headers etc
    * modify the parameters without recompilation i.e. via JSON config file.
        * https://github.com/dropbox/json11
        * https://github.com/kazuho/picojson
    * render poligons not spheres
*/

void render(sf::RenderWindow& window)
{
    auto size = window.getSize();
    float width = size.x;
    float height = size.y;
    auto aspect_ratio = width / height;

    sf::VertexArray framebuffer(sf::Points, width*height);  // reuse the buffer?

    omega::Vector origin(0, 0, 0);  // of the camera

    // Sphere
    omega::Vector center(0, 0, -3); // defined in the screen space coordinates?
    omega::Sphere sphere(center, 1);

    // Light
    omega::Light light(-10, -10, -3, 2);

    // Cast rays
    for (size_t j = 0; j<height; j++) {
        for (size_t i = 0; i<width; i++) {
            int index = i+j*width;
            framebuffer[index].position = sf::Vector2f(i, j);

            // Convert a pixel's coordinates to screen space with account for aspect ratio and FOV
            // https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-generating-camera-rays/generating-camera-rays
            float x = (2 * (i + 0.5) / width - 1) * aspect_ratio * fov;
            float y = (1 - 2 * (j + 0.5) / height) * fov;

            omega::Vector dest(x, y, -1);
            omega::Vector light_dir = (light.position - dest);
            light_dir.Normalize();
            dest.Normalize();

            if (sphere.intersects(origin, dest)) {
                auto intensity = (light.intensity * std::max(0.f, light_dir.Dot(dest)));
                framebuffer[index].color = sf::Color::Red;
                framebuffer[index].color.r = 255 * intensity;  // reduce the saturation to emulate shadow
            } else {
                framebuffer[index].color = sf::Color::Blue;
            }
        }
    }

    window.draw(framebuffer);
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(init_width, init_height), "Test");

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.resetGLStates();
        window.clear(sf::Color::Green);
        // the function should not accept "window" but instead work on updating the vertex array
        // which should be created once...
        render(window);  
        window.display();
    }

    return 0;
}
