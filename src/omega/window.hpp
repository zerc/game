#include <memory>
#include <string>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

static sf::Color BACKGROUND(174, 174, 174);

/*
 * Defines public interface to use within the application.
 */
class WindowInterface {
    protected:
        bool alive = false;
        int frames_so_far = 0;

        void incr_frames_count() {
            if (frames_so_far >= 99999) {
                // does not make sense to go higher
                return;
            } else {
                frames_so_far++;
            }
        }

    public:
        virtual int get_width() const =0;
        virtual int get_height() const =0;
        virtual bool is_alive() =0;
        virtual void display(const sf::VertexArray& framebuffer) =0;

        int get_frames_count() {
            return frames_so_far;
        }

        void reset_frames_count() {
            frames_so_far = 0;
        }
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

        int get_width() const override;
        int get_height() const override;
        bool is_alive() override;
        void display(const sf::VertexArray& framebuffer) override;
};

std::shared_ptr<WindowInterface> create_window(float width, float height, std::string title);
