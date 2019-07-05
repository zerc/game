#include "raycaster.hpp"

void RayCaster::cast_rays(const std::map<std::string,BaseObject*>& objects) {
    auto aspect_ratio = width / height;
    Vector origin(0, 0, 0);  // of the camera
    bool point_occupied = false;

    for (auto j = 0; j<height; j++) {
        for (auto i = 0; i<width; i++) {
            int index = i+j*width;
            framebuffer[index].position = sf::Vector2f(i, j);

            // Convert a pixel's coordinates to screen space with account for aspect ratio and FOV
            // https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-generating-camera-rays/generating-camera-rays
            float x = (2 * (i + 0.5) / width - 1) * aspect_ratio * FOV;
            float y = (1 - 2 * (j + 0.5) / height) * FOV;

            Vector dest(x, y, -1);
            dest.normalize();
            point_occupied = false;  // TODO: collisions?

            for (const auto &pair : objects) {
                if (pair.second->intersects(origin, dest)) {
                    framebuffer[index].color = sf::Color::Red;
                    point_occupied = true;
                }
            }

            if (!point_occupied) {
                framebuffer[index].color = sf::Color::Blue;
            }
        }
    }
};
