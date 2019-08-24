#include <catch2/catch.hpp>

#include "../matrix.hpp"


TEST_CASE("Check public API", "[public-api]") {
    Matrix3x3 m = Matrix3x3(
        0, 1, 2,
        3, 4, 5,
        6, 7, 8);

    SECTION("Check slice") {
        REQUIRE(m(0, 0) == 0.0f);
        REQUIRE(m(0, 1) == 1.0f);
        REQUIRE(m(0, 2) == 2.0f);

        REQUIRE(m(1, 0) == 3.0f);
        REQUIRE(m(1, 1) == 4.0f);
        REQUIRE(m(1, 2) == 5.0f);

        REQUIRE(m(2, 0) == 6.0f);
        REQUIRE(m(2, 1) == 7.0f);
        REQUIRE(m(2, 2) == 8.0f);
    }

    SECTION("Assigning through slice") {
        m(2, 2) = 10.0f;
        REQUIRE(m(2, 2) == 10.0f);
    }

    SECTION("Check operator *") {
        Vector v = Vector(3, 4, 1);
        Vector result = m * v;
        auto expected_result = Vector(6, 30, 54);

        REQUIRE(result == expected_result);
    }
}

