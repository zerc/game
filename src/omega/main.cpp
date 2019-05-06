#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include "o_math.hpp"

const float width    = 200;
const float height   = 200;
const float fov    = 1;  // tan(90/2) i.e. FOV is 90 degree
auto aspect_ratio = width / height;

/*
Logic:

1. Cast rays: from origin (0, 0, 0) to center of each pixel from the framebuffer.
2. For each ray need to check either it intersects with the Sphere or not
3. Render: based on [2] draw pixels differently

Objects:

    Vector - just to work with (x, y, z)
    Sphere - to represent an object (center, radius)
*/

void render(sf::RenderWindow& window)
{
    sf::VertexArray framebuffer(sf::Points, width*height);

    omega::Vector origin(0, 0, 0);  // of the camera

    // Sphere
    omega::Vector center(0, 0, -10); // WTF is this coordinates?
    omega::Sphere sphere(center, 2);

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
            dest.Normalize();

            if (sphere.intersects(origin, dest)) {
                framebuffer[index].color = sf::Color::Red;
            } else {
                framebuffer[index].color = sf::Color::Blue;
            }
        }
    }

    window.draw(framebuffer);
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(width, height), "Test");

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

        window.clear(sf::Color::Green);
        render(window);
        window.display();
    }

    return 0;
}