#ifndef OMEGA_RAYCASTER_H
#define OMEGA_RAYCASTER_H

#include <SFML/Graphics/VertexArray.hpp>
#include <memory>

#include "config.hpp"
#include "base_object.hpp"
#include "window.hpp"

class RayCasterInterface {
    protected:
        float width = 0;
        float height = 0;
        const float FOV = 1;  // 1 == tan(90/2) i.e. FOV is 90 degree

    public:
        virtual void cast_rays(const std::map<std::string,BaseObject*>& objects, const Scene& scene) =0;
};


class RayCaster: public RayCasterInterface {
    public:
        sf::VertexArray framebuffer;

        explicit RayCaster(const std::shared_ptr<WindowInterface> w) : framebuffer()  {
                width = w->get_width();
                height = w->get_height();
                framebuffer.setPrimitiveType(sf::Points);
                framebuffer.resize(width*height);
        };

        void cast_rays(const std::map<std::string,BaseObject*>& objects, const Scene& scene) override;

        sf::Color get_color_for_material(const std::shared_ptr<Material> mat);
};

#endif
