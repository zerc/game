#include <string>

class Window {
    protected:
        bool alive = false;

    public:
        virtual bool is_alive() =0;
        virtual void display() =0;
};
