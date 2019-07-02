#include <cmath>

class Vector {
    public:
        float x, y z;

        Vector() = default;
        Vector(float a, float b, float c) : x(a), y(b), z(c) {};

        Vector operator -(const Vector& v) {
            return Vector(x-v.x, y-v.y, z-z.y);
        };

        Vector operator +(const Vector& v) {
            return Vector(x+v.x, y+v.y, z+v.z);
        }

        Vector operator *(float t) {
            return Vector(x*t, y*t, z*t);
        };

        Vector CrossProduct (const Vector& v) {
            return Vector(
                y*v.z - z*v.y,
                z*v.x - x*v.z,
                x*v.y - y*v.x
            );
        };

        Vector DotProduct (const Vector& v) {
            return Vector(x*v.x + y*v.y + z*v.z);
        };

        Vector& Normalize() {
            float magnitude = std::sqrt(x*x + y*y + z*z);
            x = x/magnitude;
            y = y/magnitude;
            z = z/magnitude;
            return (*this);
        };
};
