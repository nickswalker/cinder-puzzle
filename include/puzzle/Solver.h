#ifndef PUZZLE_SOLVER_H
#define PUZZLE_SOLVER_H

#include "Fact.h"
#include "Puzzle.h"

namespace Puzzle {
    class Solver {
        virtual std::vector<std::vector<Fact::Ptr>> solve(const Puzzle &puzzle) = 0;
    };
}
#endif //PUZZLE_SOLVER_H
