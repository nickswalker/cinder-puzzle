#ifndef PUZZLE_ASPSOLVER_H
#define PUZZLE_ASPSOLVER_H

#include <clingo.hh>
#include <puzzle/Solver.h>
#include "Puzzle.h"

namespace Puzzle {

    class ASPSolver : public Solver {
    protected:
        Clingo::Logger logger;
        Clingo::Control control;
    public:
        ASPSolver();

        void add(const std::string &fragment);

        void load(const std::string &path);

        std::vector<Fact::Ptr> solve(const Puzzle &puzzle) override;
    };

}

#endif //PUZZLE_ASPSOLVER_H
