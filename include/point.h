/** \file point.h
 *  \brief Point header
 */

#ifndef __POINT_H__
#define __POINT_H__

#include <ostream>

class Point {
public:
    Point(long x = 0, long y = 0);
    Point(const Point&);
    Point& operator=(const Point&);

    long X() const;
    void X(long);
    long Y() const;
    void Y(long);

    Point& operator+=(const Point&);
    Point& operator-=(const Point&);
    friend Point operator+(const Point&, const Point&);
    friend Point operator-(const Point&, const Point&);
    friend bool operator==(const Point&, const Point&);
    friend bool operator!=(const Point&, const Point&);
    friend std::ostream& operator<<(std::ostream&, const Point&);
private:
    long x;
    long y;
};

#endif /* define __POINT_H__ */