#ifndef OMEGA_BASE_OBJECTS_H
#define OMEGA_BASE_OBJECTS_H

class BaseObject {
    public:
        std::string name;
        std::shared_ptr<Material> material;

        virtual float intersects(const Vector& origin, const Vector& dest, bool edges) =0;
        virtual void rotate(float angle) =0;
};

#endif
