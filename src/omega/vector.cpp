#include "vector.hpp"

bool operator==(const Vector &lhs, const Vector &rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
};

bool operator!=(const Vector &lhs, const Vector &rhs) {
    return !(lhs == rhs);
};
