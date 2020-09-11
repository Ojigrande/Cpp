#include "point.h"

std::ostream & operator << (std::ostream &out, const Point &p)
{
    out << static_cast<int>(p.x) << " " << static_cast<int>(p.y);
    return out;
}
