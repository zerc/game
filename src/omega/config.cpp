#include <memory>
#include <variant>
#include <fstream>

#include "config.hpp"
#include <yaml-cpp/yaml.h>

Config::Config(std::string& raw) {
    YAML::Node node = YAML::Load(raw);

    scene.width = node["scene"]["width"].as<float>();
    scene.height = node["scene"]["height"].as<float>();
    scene.title = node["scene"]["title"].as<std::string>();
    scene.background = node["scene"]["background"].as<std::string>();
};


std::variant<std::string,int> load_raw_config(const std::string& filename) {

    std::ifstream f(filename, std::ios::ate);

    if (!f.is_open()) {
        return FILE_OPEN_ERROR;
    }
    
    auto size = f.tellg();
    std::string output(size, '\0');
    f.seekg(0);

    if (f.read(&output[0], size)) {
        return output;
    } else {
        return FILE_READ_ERROR;
    }
};
