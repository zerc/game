#include <string>
#include <istream>

struct Scene {
    float width;
    float height;
    std::string background;
};

class Config {
    public:
        Scene scene;
        
        Config(std::string& raw);
};
