#include <iostream>
#include <string>

#include "config.cpp"
#include "window.cpp"
#include "objects.cpp"

int main() {
    auto raw_config = load_raw_config("config.yaml");

    if (std::holds_alternative<int>(raw_config)) {
        int error_code = *std::get_if<int>(&raw_config);
        std::cout << "Can't construct the config file. Error code: " << error_code << std::endl;
        return 1;
    }

    auto config = Config(*std::get_if<std::string>(&raw_config));
    auto window = create_window(config.scene.width, config.scene.height, config.scene.title);

    std::vector<std::shared_ptr<BaseObject>> objects;
    create_objects(config.objects, objects);

    for (auto i=0; i<objects.size(); i++) {
        std::cout << i << std::endl;
        std::cout << objects[i]->name << std::endl;
    }
        
    while (window->is_alive()) {
        window->display();
    }

    return 0;
}
