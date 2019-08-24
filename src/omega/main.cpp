#include <iostream>
#include <thread>

#include "utils/stat.h"
#include "objects.hpp"
#include "window.hpp"
#include "raycaster.hpp"
#include "fps_counter.hpp"


void apply_transformations(std::map<std::string, BaseObject *> map);

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

    RayCaster rayCaster(window);
    FPSCounter fps_counter(window);

    struct stat attrib;
    stat("config.yaml", &attrib);
    auto updated = attrib.st_mtime;

    while (window->is_alive()) {
        rayCaster.cast_rays(objects, config.scene);
        window->display(rayCaster.framebuffer);
        apply_transformations(objects);

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

        std::this_thread::sleep_for(config.getRenderDelay());
    }

    return 0;
}

