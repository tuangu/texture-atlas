/** \file point.h
 *  \brief Point header
 */

#ifndef __POINT_H__
#define __POINT_H__

#include <ostream>

class Point {
public:
    using Coord = int;

    Point(Coord x = 0, Coord y = 0);
    Point(const Point&);
    Point& operator=(const Point&);

    Coord X() const;
    void X(Coord);
    Coord Y() const;
    void Y(Coord);

    Point& operator+=(const Point&);
    Point& operator-=(const Point&);
    friend Point operator+(const Point&, const Point&);
    friend Point operator-(const Point&, const Point&);
    friend bool operator==(const Point&, const Point&);
    friend bool operator!=(const Point&, const Point&);
    friend std::ostream& operator<<(std::ostream&, const Point&);
private:
    Coord x;
    Coord y;
};

#endif /* define __POINT_H__ */