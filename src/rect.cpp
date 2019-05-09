/** \file rect.cpp
 *  \brief Rect implementation
 */

#include "rect.h"

Rect::Rect(Coord x, Coord y, Coord w, Coord h):
    pOrigin(Point{x, y}),
    pExtent(Point{x+w, y+h}) {

}

Rect::Rect(const Point& origin, const Point& extent):
    pOrigin{origin},
    pExtent{extent} {

}

Rect::Coord Rect::width() const {
    return pExtent.X() - pOrigin.X();
}

void Rect::width(Coord w) {
    pExtent.X(pOrigin.X() + w);
}

Rect::Coord Rect::height() const {
    return pExtent.Y() - pOrigin.Y();
}

void Rect::height(Coord h) {
    pExtent.Y(pOrigin.Y() + h);
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