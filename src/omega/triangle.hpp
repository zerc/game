class Triangle : public BaseObject {
    public:
        Vector A;
        Vector B;
        Vector C;

        Triangle(const std::string s, Vector& a, Vector& b, Vector& c, std::shared_ptr<Material> mat) : A(a), B(b), C(c) {
            material = mat;
            name = s;
        }

        float intersects(const Vector& origin, const Vector& dest, bool edges);

        Vector& operator [](int i) {
            if (i == 0) {
                return A;
            } else if (i == 1) {
                return B;
            } else {
                return C;
            }
        };

        Vector& at(int i) {
            if (i == 0) {
                return A;
            } else if (i == 1) {
                return B;
            } else {
                return C;
            }
        };
};
