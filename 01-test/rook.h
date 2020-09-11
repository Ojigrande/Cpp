#ifndef ROOK_H
#define ROOK_H
#include <iostream>
#include <string>
#include <list>
#include "point.h"

class Rook
{
public:
    Rook(const std::string& name);
    Rook(const std::string& name, const Point& point);
    Rook(const std::string& name, const uint8_t x, const uint8_t y);

    void set(const Point& point);
    inline Point currentPos(void) const {return m_point;}
    inline const std::string& name(void) const {return m_name;}

    void moveTo(const Point& point);
    std::list<Point> getPathTo(const Point& point) const;

private:
    std::string m_name;
    Point       m_point;
};

#endif // ROOK_H
