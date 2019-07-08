class Triangle : public BaseObject {
    public:
        Vector A;
        Vector B;
        Vector C;

        Triangle(const std::string s, Vector& a, Vector& b, Vector& c) : A(a), B(b), C(c) {
            name = s;
        }

        bool intersects(const Vector& origin, const Vector& dest);

        Vector& operator [](int i) {
            if (i == 0) {
                return A;
            } else if (i == 1) {
                return B;
            } else {
                return C;
            }
        };
};
