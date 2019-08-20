#include <variant>
#include <map>
#include <iostream>
#include <string>

#include "utils/stat.h"
#include "config.hpp"
#include "window.cpp"
#include "objects.cpp"
#include "raycaster.cpp"
#include "fps_counter.hpp"


int main() {
    auto raw_config = load_raw_config("config.yaml");

    if (std::holds_alternative<int>(raw_config)) {
        int error_code = *std::get_if<int>(&raw_config);
        std::cout << "Can't construct the config file. Error code: " << error_code << std::endl;
        return 1;
    }

    auto config = Config(*std::get_if<std::string>(&raw_config));
    auto window = create_window(config.scene.width, config.scene.height, config.scene.title);

    std::map<std::string,BaseObject*> objects;
    create_objects(config.objects, objects);

    RayCaster raycaster(window);
    FPSCounter fps_counter(window);

    struct stat attrib;
    stat("config.yaml", &attrib);
    auto updated = attrib.st_mtime;

    while (window->is_alive()) {
        raycaster.cast_rays(objects, config.scene);
        window->display(raycaster.framebuffer);
        fps_counter.display();

        // reload the config if changed
        stat("config.yaml", &attrib);

        if (attrib.st_mtime > updated) {
            raw_config = load_raw_config("config.yaml");

            if (std::holds_alternative<int>(raw_config)) {
                int error_code = *std::get_if<int>(&raw_config);
                std::cout << "Can't construct the config file. Error code: " << error_code << std::endl;
                continue;
            }

            config = Config(*std::get_if<std::string>(&raw_config));
            create_objects(config.objects, objects);

            updated = attrib.st_mtime;
        }
    }

    return 0;
}
