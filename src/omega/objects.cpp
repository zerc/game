#include <cmath>
#include <exception>
#include "objects.hpp"

float Sphere::intersects(const Vector& origin, const Vector& dest, bool edges) {
    auto L = (center - origin);
    float tca = L.dot_product(dest);

    if (tca < 0) {
        return -1;
    }

    float d = L.dot_product(L) - tca*tca;
    float r = radius * radius;

    if (d > r) {
        return -1;
    }

    return std::abs(L.z);
};

float Triangle::intersects(const Vector& origin, const Vector& dest, bool edges) {
    // Calculate the plan's normal
    auto CA = C - A;
    auto BA = B - A;
    auto planes_normale = CA.cross_product(BA);
    planes_normale.normalize();

    float distance_from_origin = planes_normale.dot_product(A);
    float t = (planes_normale.dot_product(origin) + distance_from_origin) / planes_normale.dot_product(dest);

    if (t < 0) {
        return -1; // the triangle is behind
    }

    Vector P = origin + dest * t;
    float limit = edges ? 0.1 : 0;

    // Checking either the intersection point inside of the triangle or not
    /* Vector *C; // the vector which is perpendicular to the triangle's plane */

    // We need to cross product between vectors constructed by:
    // * vertexes edges i.e. CA, BC, AB
    // * intersection point from the same point of the triangle i.e. PA, PC, PB
    // All the dot products of between those vectors should be greater than 0 means the P
    // stands on the left hand side -> inside of the triangle.
    auto PA = P - A;
    auto C1 = CA.cross_product(PA);
    if (planes_normale.dot_product(C1) < limit) {
        return edges ? std::abs(P.z) : -1;
    }

    auto BC = B - C;
    auto PC = P - C;
    auto C2 = BC.cross_product(PC);
    if (planes_normale.dot_product(C2) < limit) {
        return edges ? std::abs(P.z) : -1;
    }

    auto AB = A - B;
    auto PB = P - B;
    auto C3 = AB.cross_product(PB);
    if (planes_normale.dot_product(C3) < limit) {
        return edges ? std::abs(P.z) : -1;
    }

    return !edges ? std::abs(P.z) : -1;
};

void create_objects(
    const std::vector<std::shared_ptr<Object>>& raw, 
    std::map<std::string,BaseObject*>& out
) {
    for (auto i=0; i < raw.size(); i++) {
        if (raw[i]->type == "triangle") {
            auto search = out.find(raw[i]->name);

            if (search != out.end()) {
                auto t = (Triangle*) search->second;
                int index = 0;

                t->material = raw[i]->material;
                t->rotation = raw[i]->rotation;

                for (auto it = raw[i]->points.begin(); it != raw[i]->points.end(); it++) {
                    // TODO: when I access attributes via "." it means the object
                    // is not a pointer but a copy?
                    t->at(index).x = (*it)[0];
                    t->at(index).y = (*it)[1];
                    t->at(index).z = (*it)[2];
                    index++;
                }

            } else {
                auto it = raw[i]->points.begin();
                Vector A(*it);
                it++;
                Vector B(*it);
                it++;
                Vector C(*it);
                out[raw[i]->name] = new Triangle(raw[i]->name, A, B, C, raw[i]->material, raw[i]->rotation);
            }
        } else if (raw[i]->type == "sphere") {
            auto search = out.find(raw[i]->name);

            if (search != out.end()) {
                auto s = (Sphere*) search->second;
                s->center = raw[i]->center;
                s->radius = raw[i]->radius;
                s->material = raw[i]->material;
                s->rotation = raw[i]->rotation;
            } else {
                out[raw[i]->name] = new Sphere(
                    raw[i]->name,
                    raw[i]->center,
                    raw[i]->radius,
                    raw[i]->material,
                    raw[i]->rotation
                );
            };
        };
    };
};


void apply_transformations(std::map<std::string, BaseObject *> objects) {
    for (const auto &pair : objects) {
        pair.second->apply_rotation();
    }
}


Matrix3x3 getRotationMatrix(const std::shared_ptr<Rotation> rotation) {
    float angle_rad = (rotation->getAngle() * M_PI / 180.0f);
    float s = std::sin(angle_rad);
    float c = std::cos(angle_rad);
    int t = rotation->getT();

    if (t == TRANSFORMATIONS::ROTATE_X) {
        return Matrix3x3(
                1, 0, 0,
                0, c, -s,
                0, s, c
        );
    }

    if (t == TRANSFORMATIONS::ROTATE_Y) {
       return Matrix3x3(
               c, 0, s,
               0, 1, 0,
               -s, 0, c
               );
    }

    if (t == TRANSFORMATIONS::ROTATE_Z) {
        return Matrix3x3(
                c, -s, 0,
                s, c, 0,
                0, 0, 1
                );
    }

    throw std::logic_error("Unknown transformation");
}

