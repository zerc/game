#ifndef OMEGA_TRIANGLE_H
#define OMEGA_TRIANGLE_H

class Triangle : public BaseObject {
    public:
        Vector A;
        Vector B;
        Vector C;

        Triangle(const std::string s, Vector& a, Vector& b, Vector& c, std::shared_ptr<Material> mat, std::shared_ptr<Rotation> rot) : A(a), B(b), C(c) {
            material = mat;
            rotation = rot;
            name = s;
        }

        float intersects(const Vector& origin, const Vector& dest, bool edges);

        void apply_rotation() {
            // checks should be done in the base class
            if (rotation == nullptr) return;
            if (rotation->getApplyNum() <= 0 || rotation->getAppliedNum() > rotation->getApplyNum()) return;

            auto m = getRotationMatrix(rotation);

            A = m * A;
            B = m * B;
            C = m * C;

            rotation->markApplied();
        }

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

#endif
