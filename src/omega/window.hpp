#include <string>

class Window {
    protected:
        bool alive;

    public:
        bool is_alive() { return alive; }
        virtual void display() =0;
};
