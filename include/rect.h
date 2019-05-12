/** \file rect.h
 *  \brief Rect header. A Rect is defined by an origin and an extent (width, and height).
 */

#ifndef __RECT_H__
#define __RECT_H__

#include <string>
#include "point.h"

class Rect {
public:
    Rect(long x = 0, long y = 0, long w = 0, long h = 0, const std::string& name = "");
    Rect(const Point& origin, const Point& extent, const std::string& name = "");

    long width() const;
    long height() const;
    long area() const;
    std::string getName() const;

    const Point& origin() const;
    void origin(Point&);
    const Point& extent() const;
    void extent(Point&);

private:
    std::string name;
    Point pOrigin;
    Point pExtent;
};

#endif /* define __RECT_H__ */