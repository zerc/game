#include "raycaster.hpp"

sf::Color RayCaster::get_color_for_material(const std::shared_ptr<Material> mat) {
    auto c = mat->color;

    switch (c)
    {
    case COLORS::RED:
        return sf::Color::Red;

    case COLORS::YELLOW:
        return sf::Color::Yellow;

    case COLORS::GREEN:
        return sf::Color::Green;
  
    default:
        return sf::Color::Black;
    };
}

void RayCaster::cast_rays(const std::map<std::string,BaseObject*>& objects, const Scene& scene) {
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
            float depth = 9999;

            for (const auto &pair : objects) {
                auto current_depth = pair.second->intersects(origin, dest, false);

                if (current_depth < 0) {
                    // nothing found
                    continue;
                }

                if (scene.edges) {
                    auto current_depth = pair.second->intersects(origin, dest, true);
                    if (current_depth < 0) {
                        // nothing found of an aedge
                        continue;
                    }
                }

                if (current_depth > depth) {
                    // current point is behind
                    continue;
                }

                depth = current_depth;
                framebuffer[index].color = get_color_for_material(pair.second->material);
                point_occupied = true;
            }

            if (!point_occupied) {
                framebuffer[index].color = sf::Color::Transparent;
            }
        }
    }
};
