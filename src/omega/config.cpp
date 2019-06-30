#include <iostream>
#include <fstream>
#include <istream>
#include "config.hpp"
#include <yaml-cpp/yaml.h>

Config::Config(std::string& raw) {
    YAML::Node node = YAML::Load(raw);

    scene.width = node["scene"]["width"].as<float>();
    scene.height = node["scene"]["height"].as<float>();
    scene.background = node["scene"]["background"].as<std::string>();
};


std::string load_raw_config(const std::string& filename) {
    std::ifstream f(filename, std::ios::ate);

    if (!f.is_open()) {
        std::cout << "can't open" << std::endl;
        return "";
    } else {
        auto size = f.tellg();
        std::string output(size, '\0');
        f.seekg(0);
        std::cout << "size " << size << std::endl;

        if(f.read(&output[0], size)) {
            return output;
        } else {
            std::cout << "can't read from the file" << std::endl;
        }
        return output;
    };
};
