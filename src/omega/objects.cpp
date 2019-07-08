#include "objects.hpp"
#include "triangle.hpp"

bool Sphere::intersects(const Vector& origin, const Vector& dest) {
    auto L = (center - origin);
    float tca = L.dot_product(dest);

    if (tca < 0) {
        return false;
    }

    float d = L.dot_product(L) - tca*tca;
    float r = radius * radius;

    if (d > r) {
        return false;
    }

    return true;
};

bool Triangle::intersects(const Vector& origin, const Vector& dest) {
    // Calculate the plan's normal
    auto CA = C - A;
    auto BA = B - A;
    auto planes_normale = CA.cross_product(BA);
    planes_normale.normalize();

    float distance_from_origin = planes_normale.dot_product(A);
    float t = (planes_normale.dot_product(origin) + distance_from_origin) / planes_normale.dot_product(dest);

    if (t < 0) {
        return false;  // the triangle is behind
    }

    Vector P = origin + dest * t;

    // Checking either the intersection point inside of the triangle or not
    /* Vector *C; // the vector which is perpendicular to the triangle's plane */

    // We need to cross product between vectors constructed by:
    // * vertexes edges i.e. CA, BC, AB
    // * intersection point from the same point of the triangle i.e. PA, PC, PB
    // All the dot products of between those vectors should be greater than 0 means the P
    // stands on the left hand side -> inside of the triangle.
    auto PA = P - A;
    auto C1 = CA.cross_product(PA);
    if (planes_normale.dot_product(C1) < 0) {
        return false;
    }

    auto BC = B - C;
    auto PC = P - C;
    auto C2 = BC.cross_product(PC);
    if (planes_normale.dot_product(C2) < 0) {
        return false;
    }

    auto AB = A - B;
    auto PB = P - B;
    auto C3 = AB.cross_product(PB);
    if (planes_normale.dot_product(C3) < 0) {
        return false;
    }

    return true;
};

void create_objects(
    const std::vector<std::shared_ptr<Object>>& raw, 
    std::map<std::string,BaseObject*>& out
) {
    for (auto i=0; i < raw.size(); i++) {
        if (raw[i]->type == "triangle") {
            /* auto search = out.find(raw[i]->name); */

            /* if (search != out.end()) { */
            /*     auto obj = (Triangle*) search->second; */
            /*     int index = 0; */

            /*     for (auto it = raw[i]->points.begin(); it != raw[i]->points.end(), it++) { */
            /*         obj[index]->x = (*it)[0]; */
            /*         index++; */

            /*         if (index > 2) { */
            /*             break;  // triangles don't have more than 3 elements */
            /*         } */
            /*     } */
            /* } else { */
                auto it = raw[i]->points.begin();
                Vector A(*it);
                it++;
                Vector B(*it);
                it++;
                Vector C(*it);


                out[raw[i]->name] = new Triangle(raw[i]->name, A, B, C);
        } else if (raw[i]->type == "sphere") {
            auto search = out.find(raw[i]->name);

            if (search != out.end()) {
                auto s = (Sphere*) search->second;
                s->center = raw[i]->center;
                s->radius = raw[i]->radius;
            } else {
                out[raw[i]->name] = new Sphere(
                    raw[i]->name,
                    raw[i]->center,
                    raw[i]->radius
                );
            };
        };
    };
};


