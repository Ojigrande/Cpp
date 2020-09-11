#ifndef BOARD_H
#define BOARD_H

#include <memory>
#include <map>
#include <unordered_map>
#include <mutex>
#include <condition_variable>

#include "rook.h"

class Rook;

class Board
{
public:
    Board();

    void addRook(std::shared_ptr<Rook> rook);
    bool moveTo(std::shared_ptr<Rook> rook, const uint8_t x = 0, const uint8_t y = 0);

private:
    bool hasEquals(const std::list<Point>& subset);

private:
    mutable std::mutex               m_mutex;
    //std::map<Point, bool, PointComp> m_mapBusy;
    std::unordered_map<Point, bool, PointHasher> m_mapBusy;
    std::condition_variable          m_cv;
};

#endif // BOARD_H
