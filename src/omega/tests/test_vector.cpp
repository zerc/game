// Tests for the Vector object
#include <vector>
#include <string>
#include <catch2/catch.hpp>

#include "../vector.hpp"

TEST_CASE("Vector constructors", "[vector-constructors]") {

    SECTION("constructed from floats") {
        float x = 0.1;
        float y = 0.2;
        float z = 0.3;

        auto v = Vector(x, y, z);

        REQUIRE(v.x == x);
        REQUIRE(v.y == y);
        REQUIRE(v.z == z);
    }

    SECTION("constructed from std::vector") {
        std::vector<float> source = {0.1, 0.2, 0.3};

        auto v = Vector(source);

        REQUIRE(v.x == 0.1f);
        REQUIRE(v.y == 0.2f);
        REQUIRE(v.z == 0.3f);
    }

    SECTION("copy") {
        auto v_one = Vector(1, 2, 3);
        auto v_two = Vector(v_one);

        REQUIRE(v_one.x == v_two.x);
        REQUIRE(v_one.y == v_two.y);
        REQUIRE(v_one.z == v_two.z);
    }
}


TEST_CASE("Vector operations", "[vector-operations]") {
    auto v_one = Vector(1, 2, 3);
    auto v_two = Vector(4, 5, 6);

    SECTION("comparison") {
        auto v = Vector(v_one);

        REQUIRE(v_one == v);
        REQUIRE(v_two != v);
    }

    SECTION("add") {
        auto expected_result = Vector(5, 7, 9);
        auto result = v_one + v_two;

        REQUIRE(result == expected_result);
    }

    SECTION("sub") {
        REQUIRE((v_two - v_one) == Vector(3, 3, 3));
        REQUIRE((v_one - v_two) == Vector(-3, -3, -3));
    }

    SECTION("multiply by a scalar") {
        REQUIRE((v_one * 3) == Vector(3, 6, 9));
    }

    SECTION("cross product") {
        REQUIRE(v_one.cross_product(v_two) == Vector(-3, 6, -3));
    }

    SECTION("dot product") {
        REQUIRE(v_one.dot_product(v_two) == 32);
    }

    SECTION("normalization") {
        v_one.normalize();

        char result [20];
        // The precision should be enough to just check that the values were calculated using the correct logic.
        sprintf(result, "%.2f %.2f %.2f", v_one.x, v_one.y, v_one.z);

        std::string expected_result = "0.27 0.53 0.80";

        REQUIRE(std::string(result) == expected_result);
    }
}
