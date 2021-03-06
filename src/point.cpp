/** \file point.cpp
 *  \brief Point implementation
 */

#include "point.h"

Point::Point(long x, long y) : x{x}, y{y} {}

Point::Point(const Point& other) : x{other.X()}, y{other.Y()} {}

Point& Point::operator=(const Point& other) {
    if (this != &other) {
        x = other.X();
        y = other.Y();
    }

    return *this;
}

long Point::X() const { return x; }

void Point::X(long x) { this->x = x; }

long Point::Y() const { return y; }

void Point::Y(long y) { this->y = y; }

Point& Point::operator+=(const Point& other) {
    x += other.x;
    y += other.y;
    return *this;
}

Point& Point::operator-=(const Point& other) {
    x -= other.x;
    y -= other.y;
    return *this;
}

Point operator+(const Point& lhs, const Point& rhs) {
    return Point{lhs.x + rhs.x, lhs.y + rhs.y};
}

Point operator-(const Point& lhs, const Point& rhs) {
    return Point{lhs.x - rhs.x, lhs.y - rhs.y};
}

bool operator==(const Point& lhs, const Point& rhs) {
    return (lhs.x == rhs.x) && (lhs.y == rhs.y);
}

bool operator!=(const Point& lhs, const Point& rhs) { return !(lhs == rhs); }

std::ostream& operator<<(std::ostream& os, const Point& point) {
    os << "(" << point.x << "," << point.y << ")";
    return os;
}