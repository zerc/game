#ifndef OMEGA_MATRIX_HPP
#define OMEGA_MATRIX_HPP

#include "vector.hpp"

class Matrix3x3 {
private:
    float n[3][3];

public:
    Matrix3x3() = default;

    Matrix3x3(
            float n00, float n01, float n02,
            float n10, float n11, float n12,
            float n20, float n21, float n22
            ) {
       n[0][0] = n00;
       n[0][1] = n01;
       n[0][2] = n02;

       n[1][0] = n10;
       n[1][1] = n11;
       n[1][2] = n12;

       n[2][0] = n20;
       n[2][1] = n21;
       n[2][2] = n22;
    }

    Matrix3x3(Vector& v1, Vector& v2, Vector& v3) {

        n[0][0] = v1.x;
        n[0][1] = v1.y;
        n[0][2] = v1.z;

        n[1][0] = v2.x;
        n[1][1] = v2.y;
        n[1][2] = v2.z;

        n[2][0] = v3.x;
        n[2][1] = v3.y;
        n[2][2] = v3.z;
    }

    Matrix3x3(Matrix3x3& m) {
        n[0][0] = m(0, 0);
        n[0][1] = m(0, 1);
        n[0][2] = m(0, 2);

        n[1][0] = m(1, 0);
        n[1][1] = m(1, 1);
        n[1][2] = m(1, 2);

        n[2][0] = m(2, 0);
        n[2][1] = m(2, 1);
        n[2][2] = m(2, 2);
    }

    float& operator()(int x, int y) {
        return n[x][y];
    }

    const float& operator()(int x, int y) const {
        return n[x][y];
    }
};

Vector operator*(const Matrix3x3& m, const Vector& v);

#endif
