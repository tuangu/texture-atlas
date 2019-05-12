#include "catch2/catch.hpp"

#include "point.h"

TEST_CASE("point can be created, added, subtracted, and compared", "[point]") {
    Point zero{0, 0};
    Point pA{1, 2};
    Point pB{4, 3};
    pB.X(3);
    pB.Y(4);
    Point pC = pA + pB;
    Point pD = pA + zero;
    Point pE = pB - zero;
    Point pF{pE};

    REQUIRE(pA.X() == 1);
    REQUIRE(pA.Y() == 2);

    REQUIRE(pC.X() == 4);
    REQUIRE(pC.Y() == 6);

    REQUIRE(pA != pB);

    REQUIRE(pA == pD);
    REQUIRE(pB == pE);
    REQUIRE(pF == pE);
}