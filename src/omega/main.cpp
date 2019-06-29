#include <iostream>
#include "yaml-cpp/yaml.h"

int main() {
    YAML::Node config = YAML::LoadFile("config.yaml");
    std::cout << config << std::endl;
    return 0;
}
