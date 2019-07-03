class Sphere : public BaseObject {
    public:
        Vector center;
        float radius;

        Sphere() = default;
        Sphere(const std::string s, const Vector& c, float r) : center(c), radius(r) {
            name = s;
        }
        Sphere(const std::string s, const std::vector<float> c, float r): center(c), radius(r) {
            name = s;
        }

        bool intersects(const Vector& origin, const Vector& dest);
};
