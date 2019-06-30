#include <iostream>
#include <string>
/* #include "config.cpp" */
#include "window.cpp"

int main() {
    auto raw_config = load_raw_config("config.yaml");
    auto config = Config(raw_config);

    create_window(config);

    /* sf::RenderWindow window(sf::VideoMode(100, 100), "Test"); */

    /* // run the program as long as the window is open */
    /* while (window.isOpen()) */
    /* { */
    /*     // check all the window's events that were triggered since the last iteration of the loop */
    /*     sf::Event event; */
    /*     while (window.pollEvent(event)) */
    /*     { */
    /*         // "close requested" event: we close the window */
    /*         if (event.type == sf::Event::Closed) */
    /*             window.close(); */
    /*     } */

    /*     window.resetGLStates(); */
    /*     window.clear(sf::Color::Green); */
    /*     window.display(); */
    /* } */

    /* YAML::Node config = YAML::LoadFile("config.yaml"); */
    /* std::cout << config << std::endl; */
    return 0;
}
