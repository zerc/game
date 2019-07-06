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

    auto elements = node["scene"]["objects"];

    for (auto i=0; i < elements.size(); i++) {
        auto obj = node["scene"]["objects"][i];

        auto tmp = std::make_shared<Object>();
        tmp->name = obj["name"].as<std::string>();
        tmp->type = obj["type"].as<std::string>();

        if (obj["center"].IsSequence()) {
            tmp->center.push_back(obj["center"][0].as<float>());
            tmp->center.push_back(obj["center"][1].as<float>());
            tmp->center.push_back(obj["center"][2].as<float>());
        }

        if (obj["radius"].IsDefined()) {
            tmp->radius = obj["radius"].as<float>();
        }

        if (obj["points"].IsDefined()) {

            if (tmp->points.size() > 0) {
                tmp->points.erase(tmp->points.begin());
            }

            for (const auto &row : obj["points"]) {
                tmp->points.push_back(std::vector<float>{
                    row[0].as<float>(),
                    row[1].as<float>(),
                    row[2].as<float>(),
                });
            }
        }

        objects.push_back(tmp);
    };
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
