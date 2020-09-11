#include <stdexcept>        // std::invalid_argument

#include "rook.h"

Rook::Rook(const std::string& name)
    : m_name(name)
    , m_point {0, 0}
{
}

Rook::Rook(const std::string& name, const Point& point)
    : Rook(name)
{
    set(point);
}

Rook::Rook(const std::string& name, const uint8_t x, const uint8_t y)
    : Rook(name)
{
    set(Point {x, y});
}

void Rook::set(const Point& point)
{
    if ( point.x == 0 || point.x > 8 )
        throw std::invalid_argument("Incorrect value of x " + std::to_string(point.x));
    if ( point.y == 0 || point.y > 8)
        throw std::invalid_argument("Incorrect value of y: " + std::to_string(point.y));

    m_point = point;
}

/*
 * Передвижение ладьи с текущей позиции в заданную позицию
 * Допустимые значения x и y от 0 до 8.
 * 0 - игнорирование перемещение по данной оси.
*/
void Rook::moveTo(const Point& point)
{
    Point newPoint = point;

    if (point.x == 0)
        newPoint.x = currentPos().x;
    else if (point.y == 0)
        newPoint.y = currentPos().y;

    set(newPoint);
}


std::list<Point> Rook::getPathTo(const Point& point) const
{
    std::list<Point> steps;
    if (point.x == 0 && point.y == 0)
        return steps;

    if ( point.x > 8 )
        throw std::invalid_argument("Incorrect value of x " + std::to_string(point.x));
    if ( point.y > 8)
        throw std::invalid_argument("Incorrect value of y: " + std::to_string(point.y));

    if (m_point.x == point.x || point.x == 0)
    {// Ход вдоль вертикали
        Point p {m_point.x, 0};
        int8_t s = m_point.y < point.y ? 1 : -1;
        for(uint8_t i(m_point.y);  i != point.y; i+=s)
        {
            p.y = static_cast<uint8_t>(static_cast<int>(i) + s);
            steps.push_back(p);
        }
    }
    else if (m_point.y == point.y || point.y == 0)
    {// Ход вдоль горизонтали
        Point p {0, m_point.y};
        int8_t s = m_point.x < point.x ? 1 : -1;
        for(uint8_t i(m_point.x);  i != point.x; i+=s)
        {
            p.x = static_cast<uint8_t>(static_cast<int>(i) + s);
            steps.push_back(p);
        }
    }
    else // m_x != x && m_y != y
        throw std::invalid_argument("Wrong move for rook.");

    return steps;
}
