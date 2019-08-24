#ifndef OMEGA_CONFIG_H
#define OMEGA_CONFIG_H

#include <chrono>
#include <variant>
#include <map>
#include <list>
#include <memory>
#include <utility>
#include <vector>
#include <string>
#include <istream>

static int FILE_OPEN_ERROR = 1;
static int FILE_READ_ERROR = 2;

namespace COLORS {
    enum color {
        RED,
        YELLOW,
        GREEN,
    };
};

namespace TRANSFORMATIONS {
    enum transformations {
        ROTATE_V, // rotation around arbitrary unit vector
    };
}

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

        Material(std::string name_, int color_) : name(std::move(name_)), color(color_) {};
};


class Rotation {
private:
    int t;
    float angle;
    float v[3];

public:
    Rotation(int t, float angle, float x, float y, float z) : t(t), angle(angle) {
        v[0] = x;
        v[1] = y;
        v[2] = z;
    }

    int getT() const {
        return t;
    }

    float getAngle() const {
        return angle;
    }

    float x() {
        return v[0];
    }

    float y() {
        return v[1];
    }

    float z() {
        return v[2];
    }
};


class Object {
    public:
        std::string name;
        std::string type;
        std::vector<float> center;
        float radius;
        std::list<std::vector<float>> points;
        std::shared_ptr<Material> material;
        std::shared_ptr<Rotation> rotation;

        Object() = default;
};

class Config {
private:
    int render_delay; // delay to set between frames

public:
    Scene scene;
    std::vector<std::shared_ptr<Object>> objects;
    std::map<std::string, std::shared_ptr<Material>> materials;

    explicit Config(std::string& raw);

    std::chrono::milliseconds getRenderDelay() const {
        return std::chrono::milliseconds(render_delay);
    }
};


std::variant<std::string,int> load_raw_config(const std::string& filename);

#endif
