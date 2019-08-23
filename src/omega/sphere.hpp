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
        Sphere(const std::string s, const Vector& c, float r, std::shared_ptr<Material> mat) : center(c), radius(r) {
            material = mat;
            name = s;
        }
        Sphere(const std::string s, const std::vector<float> c, float r, std::shared_ptr<Material> mat): center(c), radius(r) {
            material = mat;
            name = s;
        }

        float intersects(const Vector& origin, const Vector& dest, bool edges);

        void rotate(float angle) {
            // ignore the parameter for now
            rotate_called_times++;

            if (rotate_called_times > 72) {
                // restore original values because we did a round
                center.x = _x;
                center.y = _y;
                center.z = _z;
                rotate_called_times = 1;
            } else if (rotate_called_times == 1) {
                _x = center.x;
                _y = center.y;
                _z = center.z;
            }

            float new_x = center.x * 0.996f - center.y * 0.087f + 0;
            float new_y = center.x * 0.087f + center.y * 0.996f + 0;
            float new_z = center.z;

            center.x = new_x;
            center.y = new_y;
            center.z = new_z;

        }
};

#endif
