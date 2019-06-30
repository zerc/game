#include <string>
#include <istream>

int FILE_OPEN_ERROR = 1;
int FILE_READ_ERROR = 2;

struct Scene {
    float width;
    float height;
    std::string title;
    std::string background;
};

class Config {
    public:
        Scene scene;
        
        Config(std::string& raw);
};
