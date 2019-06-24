#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include "o_math.hpp"

const float init_width    = 640;
const float init_height   = 480;
const float fov    = 1;  // tan(90/2) i.e. FOV is 90 degree


/*
 * Returns True when the ray lands on the edge of the vertex.
 */
bool omega::Vertex::edge_intersects (Vector& origin, Vector& dest) {
    // Calculate the plan's normal
    auto CA = C - A;
    auto BA = B - A;
    auto planes_normale = CA.Cross(BA);
    planes_normale.Normalize();

    auto distance_from_origin = planes_normale.Dot(A);
    float t = (planes_normale.Dot(origin) + distance_from_origin) / planes_normale.Dot(dest);

    if (t < 0) {
        return false;  // the vertex is behind
    }

    omega::Vector P = origin + dest * t;

    auto PA = P - A;
    auto C1 = CA.Cross(PA);
    // given that we use this method after `intersects` i.e. we know that the P inside of the vertex
    // so we just need to select the most "left" subset of points to draw an edge
    if (planes_normale.Dot(C1) <= 0.05) {  
        return true;
    }

    auto BC = B - C;
    auto PC = P - C;
    auto C2 = BC.Cross(PC);
    if (planes_normale.Dot(C2) <= 0.05) {
        return true;
    }

    auto AB = A - B;
    auto PB = P - B;
    auto C3 = AB.Cross(PB);
    if (planes_normale.Dot(C3) <= 0.05) {
        return true;
    }

    return false;

    /*
    auto PA = P - A;
    PA.Normalize();
    CA.Normalize();
    auto cos = CA.Dot(PA);
    if (cos >= 0.999) {
        return true;
    }

    auto BC = B - C;
    auto PC = P - C;
    BC.Normalize();
    PC.Normalize();
    cos = BC.Dot(PC);
    if (cos >= 0.999) {
        return true;
    }

    auto AB = A - B;
    auto PB = P - B;
    cos = AB.Dot(PB) / (AB.Magnitude() * PB.Magnitude());
    if (cos >= 0.999) {  // since we call the method only for points inside the triangle we don't need to check the top end
        return true;
    }

    return false;
    */
};

/*
 * https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-rendering-a-triangle/ray-triangle-intersection-geometric-solution
 */
bool omega::Vertex::intersects (Vector& origin, Vector& dest) {
    // Calculate the plan's normal
    auto CA = C - A;
    auto BA = B - A;
    auto planes_normale = CA.Cross(BA);
    planes_normale.Normalize();

    auto distance_from_origin = planes_normale.Dot(A);
    float t = (planes_normale.Dot(origin) + distance_from_origin) / planes_normale.Dot(dest);

    if (t < 0) {
        return false;  // the vertex is behind
    }

    omega::Vector P = origin + dest * t;

    // Checking either the intersection point inside of the vertex or not
    /* omega::Vector *C; // the vector which is perpendicular to the vertex's plane */

    // We need to cross product between vectors constructed by:
    // * vertexes edges i.e. CA, BC, AB
    // * intersection point from the same point of the vertex i.e. PA, PC, PB
    // All the dot products of between those vectors should be greater than 0 means the P
    // stands on the left hand side -> inside of the triangle.
    auto PA = P - A;
    auto C1 = CA.Cross(PA);
    if (planes_normale.Dot(C1) < 0) {
        return false;
    }

    auto BC = B - C;
    auto PC = P - C;
    auto C2 = BC.Cross(PC);
    if (planes_normale.Dot(C2) < 0) {
        return false;
    }

    auto AB = A - B;
    auto PB = P - B;
    auto C3 = AB.Cross(PB);
    if (planes_normale.Dot(C3) < 0) {
        return false;
    }

    return true;
}

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
        * https://github.com/nlohmann/json
        * https://github.com/dropbox/json11
        * https://github.com/kazuho/picojson
    * render poligons not spheres. Support OBJ format: http://paulbourke.net/dataformats/obj/
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

    // Vertex
    omega::Vector a = omega::Vector(-1, -1, -3);
    omega::Vector b = omega::Vector(1, -1, -3);
    omega::Vector c = omega::Vector(0, 1, -3);
    omega::Vertex vertex1(a, b, c);

    omega::Vector a1 = omega::Vector(1, -1, -3);
    omega::Vector b1 = omega::Vector(0, 1, -3);
    omega::Vector c1 = omega::Vector(1, 0, -3);
    omega::Vertex vertex2(a1, b1, c1);

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

            if (vertex1.intersects(origin, dest)) {
                if (vertex1.edge_intersects(origin, dest)) {
                    framebuffer[index].color = sf::Color::Green;
                } else {
                    framebuffer[index].color = sf::Color::Red;
                }

            /* if (sphere.intersects(origin, dest)) { */
            /*     auto intensity = (light.intensity * std::max(0.f, light_dir.Dot(dest))); */
            /*     framebuffer[index].color = sf::Color::Red; */
            /*     framebuffer[index].color.r = 255 * intensity;  // reduce the saturation to emulate shadow */
            } else if (vertex2.intersects(origin, dest)) {
                if (vertex2.edge_intersects(origin, dest)) {
                    framebuffer[index].color = sf::Color::Green;
                } else {
                    framebuffer[index].color = sf::Color::Yellow;
                }
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
