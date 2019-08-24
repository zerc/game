#include "matrix.hpp"

Vector operator*(const Matrix3x3& m, const Vector& v) {
    return Vector(
            m(0,0) * v.x + m(0,1) * v.y + m(0,2) * v.z,
            m(1,0) * v.x + m(1,1) * v.y + m(1,2) * v.z,
            m(2,0) * v.x + m(2,1) * v.y + m(2,2) * v.z
    );
}


