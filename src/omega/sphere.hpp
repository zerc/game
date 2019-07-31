class Sphere : public BaseObject {
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

        bool intersects(const Vector& origin, const Vector& dest, bool edges);
};
