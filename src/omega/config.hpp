#include <list>
#include <memory>
#include <vector>
#include <string>
#include <istream>

int FILE_OPEN_ERROR = 1;
int FILE_READ_ERROR = 2;

namespace COLORS {
    enum color {
        RED,
        YELLOW,
        GREEN,
    };
};

struct Scene {
    float width;
    float height;
    std::string title;
    std::string background;
    bool edges;
};

class Material {
    public:
        std::string name;
        int color;

        Material(std::string name_, int color_) : name(name_), color(color_) {};
};

class Object {
    public:
        std::string name;
        std::string type;
        std::vector<float> center;
        float radius;
        std::list<std::vector<float>> points;
        std::shared_ptr<Material> material;

        Object() = default;
};

class Config {
    public:
        Scene scene;
        std::vector<std::shared_ptr<Object>> objects;
        std::map<std::string, std::shared_ptr<Material>> materials;
        
        Config(std::string& raw);
};
