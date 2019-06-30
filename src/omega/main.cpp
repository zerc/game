#include <iostream>
#include <string>

#include "config.cpp"
#include "window.cpp"

int main() {
    auto raw_config = load_raw_config("config.yaml");

    if (std::holds_alternative<int>(raw_config)) {
        int error_code = *std::get_if<int>(&raw_config);
        std::cout << "Can't construct the config file. Error code: " << error_code << std::endl;
        return 1;
    }

    auto config = Config(*std::get_if<std::string>(&raw_config));
    create_window(config.scene.width, config.scene.height);

    return 0;
}
