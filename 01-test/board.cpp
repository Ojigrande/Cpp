#include <iostream>
#include <chrono>

#include "board.h"
#include "rook.h"

Board::Board()
{
}

void Board::addRook(std::shared_ptr<Rook> rook)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    m_mapBusy.insert( std::pair<Point, bool>(rook->currentPos(), false) );
}

/* Функция осуществляет ход на шахматной доске.
 *
 * Если путь для фигуры преграждает другая, то ждем когда путь освободится.
 *
 * Возвращает true, если ход был сделан.
 * false - вышло время ожидания
*/
bool Board::moveTo(std::shared_ptr<Rook> rook, const uint8_t x, const uint8_t y)
{
    Point point {x, y};
    auto path = rook->getPathTo(point);

    std::unique_lock<std::mutex> lock(m_mutex);

    while ( hasEquals(path) )
    {// Ждем 5 секунд и если путь не освободили, то идем в другую сторону
        if ( m_cv.wait_for(lock, std::chrono::seconds(5)) == std::cv_status::timeout )
        {
            std::cout << "Time out: " << rook->name() << std::endl;
            return false;
        }
    }

    // Путь свободен. Мы идем
    Point old_point = rook->currentPos();
    try {

        bool needwakeUp = m_mapBusy[old_point];

        std::cout << rook->name() << ": " << old_point;
        rook->moveTo(point);

        m_mapBusy.erase(old_point);
        m_mapBusy.insert( std::pair<Point, bool>(rook->currentPos(), false) );
        std::cout << " -> " << rook->currentPos() << std::endl;

        // Разбудим всех ожидающих смещения данной фигуры
        lock.unlock();
        if (needwakeUp)
            m_cv.notify_all();
    } catch (const std::invalid_argument& e) {
        std::cout << e.what() << std::endl;
        std::cout << "Rook hasn't been moved." << std::endl;
        return false;
    }
    return true;
}

bool Board::hasEquals(const std::list<Point>& lst)
{
    bool retValue = false;

    for (auto p: lst)
    {
        auto it = m_mapBusy.find(p);
        if ( it != m_mapBusy.end() )
        {
            it->second = true;
            retValue = true;
        }
    }
    return retValue;
}
