#ifndef PUZZLE_POINT_H
#define PUZZLE_POINT_H

#include <puzzle/Fact.h>
#include <sstream>

namespace Puzzle {
    class Point : public Fact {
    public:
        typedef std::shared_ptr<Point> Ptr;

        size_t x;
        size_t y;

        explicit Point(size_t x, size_t y) : x(x), y(y) {};

        std::string to_string() override {
            std::ostringstream out;
            out << "point(x=" << x << " y=" << y << ").";
            return out.str();

        }
    };
}


#endif //PUZZLE_POINT_H
