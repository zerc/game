#include <cmath>

namespace omega {
    class Vector {
        float x, y, z;
        bool normalized;

        public:
            Vector (float x_, float y_, float z_) : x(x_), y(y_), z(z_) {
                normalized = false;
            };

            Vector operator -(const Vector& v) {
                return Vector(x - v.x, y - v.y, z - v.z);
            };

            Vector operator +(const Vector& v) {
                return Vector(x + v.x, y + v.y, z + v.z);
            };

            // Calculates dot product between current vector and the given one (v)
            float Dot (const Vector& v) {
                return x*v.x + y*v.y + z*v.z;
            };

            float Magnitude() {
                return std::sqrt(x*x + y*y + z*z);
            };

            void Normalize() {
                float m = Magnitude();
                x = x/m;
                y = y/m;
                z = z/m;
                normalized = true;
            };

            bool IsNormalised() {
                return normalized;
            };
    };

    class Sphere {
        Vector& center;
        float radius;

        public:
            Sphere (Vector& c, float r) : center(c), radius(r) {};
            bool intersects(Vector& origin, Vector& dest);
    };

    class Light {
        public:
            Light(const float x, const float y, const float z, const float i): position(x, y, z), intensity(i) {};
            Vector position;
            float intensity;
    };

    /*
     * Returns either the vector given by (origin, dest) is intersecting with the shpere or not.
     * http://www.lighthouse3d.com/tutorials/maths/ray-sphere-intersection/ 
     * https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-sphere-intersection
     * NOTE: `dest` is expected to be normalised vector
     */
    bool Sphere::intersects (Vector& origin, Vector& dest) {
        auto L = (center - origin);
        float tca = L.Dot(dest);

        if (tca < 0) {
            return false;
        }

        float d = L.Dot(L) - tca*tca;
        float r = radius * radius;

        if (d > r) {
            return false;
        }

        return true;
    }
};
