#ifndef OMEGA_SPHERE_H
#define OMEGA_SPHERE_H

class Sphere : public BaseObject {
    private:
        float _x;
        float _y;
        float _z;
        int rotate_called_times = 0;

    public:
        Vector center;
        float radius;

        Sphere() = default;
        Sphere(const std::string s, const Vector& c, float r, std::shared_ptr<Material> mat, std::shared_ptr<Rotation> rot) : center(c), radius(r) {
            material = mat;
            rotation = rot;
            name = s;
        }
        Sphere(const std::string s, const std::vector<float> c, float r, std::shared_ptr<Material> mat, std::shared_ptr<Rotation> rot): center(c), radius(r) {
            material = mat;
            rotation = rot;
            name = s;
        }

        float intersects(const Vector& origin, const Vector& dest, bool edges);

        void apply_rotation() {
            if (rotation == nullptr) return;
            if (rotation->getApplyNum() <= 0 || rotation->getAppliedNum() > rotation->getApplyNum()) return;
            auto m = getRotationMatrix(rotation);
            center = m * center;
            rotation->markApplied();
        }
};

#endif
