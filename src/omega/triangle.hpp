class Triangle : public BaseObject {
    public:
        Vector& A;
        Vector& B;
        Vector& C;

        Triangle(const Vector& a, const Vector& b, const Vector& c) : A(a), B(b), C(c) {};
        bool intersects(const Vector& origin, const Vector& dest) override;
}
