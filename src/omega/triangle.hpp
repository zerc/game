#ifndef OMEGA_TRIANGLE_H
#define OMEGA_TRIANGLE_H

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

        void rotate(float angle) {
            // ignore the parameter for now
            float new_x = A.x * 0.996f + A.y * 0 + A.z * 0.087f;
            float new_y = A.x * 0 + A.y * 1 + A.z * 0;
            float new_z = A.x * -0.087f + A.y * 0 + A.z * 0.996f;

            A.x = new_x;
            A.y = new_y;
            A.z = new_z;

            new_x = B.x * 0.996f + B.y * 0 + B.z * 0.087f;
            new_y = B.x * 0 + B.y * 1 + B.z * 0;
            new_z = B.x * -0.087f + B.y * 0 + B.z * 0.996f;

            B.x = new_x;
            B.y = new_y;
            B.z = new_z;

            new_x = C.x * 0.996f + C.y * 0 + C.z * 0.087f;
            new_y = C.x * 0 + C.y * 1 + C.z * 0;
            new_z = C.x * -0.087f + C.y * 0 + C.z * 0.996f;

            C.x = new_x;
            C.y = new_y;
            C.z = new_z;
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
