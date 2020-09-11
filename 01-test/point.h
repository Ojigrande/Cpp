#ifndef POINT_H
#define POINT_H
#include <iostream>
#include <cstdint>          // uint8

struct Point
{
    std::uint8_t x, y;
    friend std::ostream & operator << (std::ostream &out, const Point &p);
    bool operator == (const Point& other) const
    {
        return (x == other.x && y == other.y);
    }
};

struct PointComp
{
    bool operator()(const Point& lhs, const Point& rhs) const
    {
        return (lhs.x < rhs.x) || ( lhs.x == rhs.x && lhs.y < rhs.y);
    }
};

struct PointHasher
{
    std::size_t operator() (const Point& p) const
    {
        using std::size_t;
        using std::hash;

        return ( (hash<uint8_t>()(p.x) << 1)
               ^ (hash<uint8_t>()(p.y)));
    }
};

#endif // POINT_H
