/** \file rect.cpp
 *  \brief Rect implementation
 */

#include "rect.h"

Rect::Rect(long x, long y, long w, long h, const std::string& name):
    name{name}, pOrigin(Point{x, y}), pExtent(Point{x+w, y+h}) {

}

Rect::Rect(const Point& origin, const Point& extent, const std::string& name):
    name{name}, pOrigin{origin}, pExtent{extent} {

}

long Rect::width() const {
    return pExtent.X() - pOrigin.X() + 1;
}

long Rect::height() const {
    return pExtent.Y() - pOrigin.Y() + 1;
}

long Rect::area() const {
    return width() * height();
}

std::string Rect::getName() const {
    return name;
}

const Point& Rect::origin() const {
    return pOrigin;
}

void Rect::origin(Point& origin) {
    pOrigin = origin;
}

const Point& Rect::extent() const {
    return pExtent;
}

void Rect::extent(Point& extent) {
    pExtent = extent;
}