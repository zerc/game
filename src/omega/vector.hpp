#include <cmath>

class Vector {
    public:
        float x, y, z;

        Vector() =default;
        Vector(float a, float b, float c) : x(a), y(b), z(c) {};
        Vector(const Vector& v) {
            x = v.x;
            y = v.y;
            z = v.z;
        }
        Vector(std::vector<float> v) : x(v[0]), y(v[1]), z(v[2]) {};

        Vector operator -(const Vector& v) {
            return Vector(x-v.x, y-v.y, z-v.z);
        }

        Vector operator +(const Vector& v) const {
            return Vector(x+v.x, y+v.y, z+v.z);
        }

        Vector operator *(float t) const {
            return Vector(x*t, y*t, z*t);
        }

        Vector cross_product (const Vector& v) {
            return Vector(
                y*v.z - z*v.y,
                z*v.x - x*v.z,
                x*v.y - y*v.x
            );
        }

        float dot_product (const Vector& v) {
            return x*v.x + y*v.y + z*v.z;
        }

        Vector& normalize() {
            float magnitude = std::sqrt(x*x + y*y + z*z);
            x = x/magnitude;
            y = y/magnitude;
            z = z/magnitude;
            return (*this);
        }
};

bool operator==(const Vector& lhs, const Vector& rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
};

bool operator!=(const Vector& lhs, const Vector& rhs) {
    return !(lhs == rhs);
};
