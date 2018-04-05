#ifndef PUZZLE_POINT_H
#define PUZZLE_POINT_H

#include <puzzle/Fact.h>
#include <sstream>

namespace Puzzle {
// TODO: Is it possible to simply have a Fact2 class which is templated for the types?
    class CycleEdge : public Fact {
    public:
        typedef std::shared_ptr<CycleEdge> Ptr;

        size_t x;
        size_t y;

        explicit CycleEdge(size_t x, size_t y) : x(x), y(y) {};

        std::string to_string() override {
            std::ostringstream out;
            out << "cycle_edge(x=" << x << " y=" << y << ").";
            return out.str();

        }
    };
}


#endif //PUZZLE_POINT_H
