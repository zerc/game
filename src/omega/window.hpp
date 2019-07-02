#include <string>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

/*
 * Defines public interface to use within the application.
 */
class WindowInterface {
    protected:
        bool alive = false;

    public:
        virtual bool is_alive() =0;
        virtual void display() =0;
};


/*
 * Actual definition of the window class with regards to the 3rd party package.
 */
class Window: public WindowInterface {
    private:
        sf::RenderWindow* window;

    public:
        Window(float width, float height, std::string title);

        ~Window() {
            delete window;
        };

        bool is_alive() override;
        void display() override;

        bool something() {
            return false;
        };
};
