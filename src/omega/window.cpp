#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "window.hpp"

class WindowSFML: public Window {
    protected:
        sf::RenderWindow* window;

    public:
        WindowSFML(float width, float height, std::string title) {
            window = new sf::RenderWindow(sf::VideoMode(width, height), title);
            alive = true;
        }

        ~WindowSFML() {
            delete window;
        }

        bool is_alive();
        void display() override;
};

bool WindowSFML::is_alive() {
    if (!alive) {
        return false;
    }
    // check all the window's events that were triggered since the last iteration of the loop
    sf::Event event;
    while (window->pollEvent(event)) {
        // "close requested" event: we close the window
        if (event.type == sf::Event::Closed) {
            window->close();
            alive = false;
        }
    }

    return alive;
};


void WindowSFML::display() {
    window->resetGLStates();
    window->clear(sf::Color::Green);
    window->display();
};


WindowSFML create_window(float width, float height, std::string title) {
    WindowSFML window(width, height, title);
    return window;
};
