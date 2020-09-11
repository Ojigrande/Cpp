#include <iostream>
#include <stdexcept>        // std::invalid_argument
#include <future>           // async
#include <list>
#include <random>

#include "rook.h"
#include "board.h"
#include "barrier.h"

#define NUMBER_OF_ROOK      5
#define NUMBER_OF_MOVES     50
#define NEXT_STEP_DELAY     200     // ms

static Barrier barrier(NUMBER_OF_ROOK);

using namespace std;

void func (shared_ptr<Rook> rook, shared_ptr<Board> board)
{
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(2, 17);

    cout << rook->name() << " : x = " << static_cast<int>(rook->currentPos().x) \
         << " y = " << static_cast<int>(rook->currentPos().y) << endl;
    board->addRook(rook);
    barrier.Wait();

    uint8_t x, y;
    for (int i(0); i < NUMBER_OF_MOVES; i++)
    {
        // Генерация хода ладьи. Предположим, что ходом может быть и стояние на месте.
        // Четные числа - ход по горизонтали.
        // Нечетные - ход по вертикали.
        int m = dis(gen);
        uint8_t shift = static_cast<uint8_t>(m/2);
        if (m % 2 == 0)
        {
            x = shift;
            y = 0;
        }
        else
        {
            x = 0;
            y = shift;
        }

        if ( board->moveTo(rook, x, y) )
        {
            // Ход был сделан. Подождем
            std::this_thread::sleep_for(std::chrono::milliseconds(NEXT_STEP_DELAY));
        }
        else i--;   // Ход потерян.
    }
}


int main()
{
    cout << "Hello VoxImplant!" << endl;

    try {
        auto board = make_shared<Board>();
        list<future<void>> futures;

        for (int i(0); i < NUMBER_OF_ROOK; i++)
        {
            uint8_t x = 1 + (3*i)%8;
            uint8_t y = 1 + i%8;
            auto a = make_shared<Rook>(to_string(i), x, y);
            futures.push_back(async(func, a, board));
        }

        for (const auto& r: futures)
        {
            r.wait();
        }
    }
    catch (const exception& e) {
        cout << e.what() << endl;
    }

    return 0;
}
