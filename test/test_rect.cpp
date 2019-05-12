#include "catch2/catch.hpp"

#include "rect.h"

TEST_CASE("Rect functionalities", "[rect]") {
    Rect rA{0, 0, 9, 4};
    Point pBOrigin{-1, -1};
    Point pBExtent{2, 2};
    Rect rB(pBOrigin, pBExtent, "B");

    REQUIRE(rA.width() == 10);
    REQUIRE(rA.height() == 5);
    REQUIRE(rB.width() == 4);
    REQUIRE(rB.height() == 4);
    REQUIRE(rB.getName() == "B");

    REQUIRE(rB.origin() == pBOrigin);
    REQUIRE(rB.extent() == pBExtent);

    Point pAOrigin{-3, -3};
    Point pAExtent{1, 1};
    rA.origin(pAOrigin);
    rA.extent(pAExtent);

    REQUIRE(rA.width() == 5);
    REQUIRE(rA.height() == 5);
}