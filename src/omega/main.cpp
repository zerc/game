#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>

const int width    = 1024;
const int height   = 768;

void render(sf::RenderWindow& window)
{
    sf::VertexArray framebuffer(sf::Points, width*height);

    for (size_t j = 0; j<height; j++) {
        for (size_t i = 0; i<width; i++) {
            int index = i+j*width;
            framebuffer[index].position = sf::Vector2f(i, j);
            framebuffer[index].color = sf::Color::Blue;
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

        window.clear(sf::Color::Red);
        render(window);
        window.display();
    }

    return 0;
}