/** \file rect.h
 *  \brief Rect header. A Rect is defined by an origin and an extent (width, and               height).
 */

#ifndef __RECT_H__
#define __RECT_H__

#include "point.h"

class Rect {
public:
    using Coord = Point::Coord;

    Rect(Coord x, Coord y, Coord w, Coord h);
    Rect(const Point& origin, const Point& extent);

    Coord width() const;
    void width(Coord);
    Coord height() const;
    void height(Coord);

    const Point& origin() const;
    void origin(Point&);
    const Point& extent() const;
    void extent(Point&);

private:
    Point pOrigin;
    Point pExtent;
};

#endif /* define __RECT_H__ */