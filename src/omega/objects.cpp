#include "objects.hpp"

bool Sphere::intersects(const Vector& origin, const Vector& dest) {
    return false;
}

void create_objects(const std::vector<std::shared_ptr<Object>>& raw, std::vector<std::shared_ptr<BaseObject>>& out) {
    for (auto i=0; i < raw.size(); i++) {
        if (raw[i]->type == "sphere") {
            out.push_back(std::make_shared<Sphere>(
                raw[i]->name,
                raw[i]->center,
                raw[i]->radius
            ));
        };
    };
};


