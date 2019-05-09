/** \file point.cpp
 *  \brief Point implementation
 */

#include "point.h"

Point::Point(Coord x, Coord y):
    x{x}, y{y} {

}

Point::Point(const Point& other):
    x{other.X()},
    y{other.Y()} {

}

Point& Point::operator=(const Point& other) {
    if (this != &other) {
        x = other.X();
        y = other.Y();
    }

    return *this;
}

Point::Coord Point::X() const {
    return x;
}

void Point::X(Coord x) {
    this->x = x;
}

Point::Coord Point::Y() const {
    return y;
}

void Point::Y(Coord y) {
    this->y = y;
}

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

bool operator!=(const Point& lhs, const Point& rhs) {
    return !(lhs == rhs);
}

std::ostream& operator<<(std::ostream& os, const Point& point) {
    os << "(" << point.x << "," << point.y << ")";
    return os;
}