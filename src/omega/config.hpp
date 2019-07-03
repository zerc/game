#include <memory>
#include <vector>
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


class Object {
    public:
        std::string name;
        std::string type;
        std::vector<float> center;
        float radius;
        /* std::vector<std::vector<float>* > points; */

        Object() = default;
};

class Config {
    public:
        Scene scene;
        std::vector<std::shared_ptr<Object>> objects;
        
        Config(std::string& raw);
};
